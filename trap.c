#include "types.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "x86.h"
#include "traps.h"
#include "spinlock.h"

// Interrupt descriptor table (shared by all CPUs).
struct gatedesc idt[256];
extern uint vectors[];  // in vectors.S: array of 256 entry pointers
struct spinlock tickslock;
uint ticks;

extern int mappages(pde_t *pgdir, void *va, uint size, uint pa, int perm);

void
tvinit(void)
{
  int i;

  for(i = 0; i < 256; i++)
    SETGATE(idt[i], 0, SEG_KCODE<<3, vectors[i], 0);
  SETGATE(idt[T_SYSCALL], 1, SEG_KCODE<<3, vectors[T_SYSCALL], DPL_USER);

  initlock(&tickslock, "time");
}

void
idtinit(void)
{
  lidt(idt, sizeof(idt));
}

//PAGEBREAK: 41
void
trap(struct trapframe *tf)
{
  uint addr;

  if(tf->trapno == T_SYSCALL){
    if(proc->killed)
      exit();
    proc->tf = tf;
    syscall();
    if(proc->killed)
      exit();
    return;
  }

  switch(tf->trapno){
  case T_IRQ0 + IRQ_TIMER:
    if(cpunum() == 0){
      acquire(&tickslock);
      ticks++;
      wakeup(&ticks);
      release(&tickslock);
    }
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE:
    ideintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_IDE+1:
    // Bochs generates spurious IDE1 interrupts.
    break;
  case T_IRQ0 + IRQ_KBD:
    kbdintr();
    lapiceoi();
    break;
  case T_IRQ0 + IRQ_COM1:
    uartintr();
    lapiceoi();
    break;
  case T_IRQ0 + 7:
  case T_IRQ0 + IRQ_SPURIOUS:
    cprintf("cpu%d: spurious interrupt at %x:%x\n", cpunum(), tf->cs, tf->eip);
    lapiceoi();
    break;

  // Caso fallo de página: reserva a posteriori
  case T_GPFLT:
    cprintf("General protection fault: pid=%d\n", proc->pid);
    proc->killed = 1;
    break;

  // Caso fallo de página: reserva a posteriori
  case T_PGFLT:
    if(proc == 0) {
      // In kernel, it must be our mistake.
      cprintf("unexpected page fault from cpu %d eip %x (cr2=0x%x)\n",
              cpunum(), tf->eip, rcr2());
      panic("trap");
    }

    // Direccion que genera el error, se redonde hacia abajo hasta límite de pagina
    // para coger la dirección del marco.
    addr = PGROUNDDOWN(rcr2());

    // Comprobamos que no estamos reservando la página de guarda.
    if (addr == proc->guardpage) {
      cprintf("Page fault error: Stack overflow. PROC->GUARDPAGE=0x%x, addr=0x%x.\n", proc->guardpage, addr);
      proc->killed = 1;
      break;
    }

    // Si está intentando mapear una dirección en el espacio de kernel, mata al proceso.
    if(addr >= KERNBASE) {
      cprintf("Page fault error: Illegal memory address: addr=0x%x.\n", addr);
      proc->killed = 1;
      break;
    }

    // Reservamos memoria
    char *mem = kalloc();

    if(mem == 0) {
      cprintf("Page fault error: Out of memory.\n");
      proc->killed = 1;
      break;
    }

    // Inicializamos a 0 toda la página.
    memset(mem, 0, PGSIZE);

    // Mapeamos una página.
    if(mappages(proc->pgdir, (char*)addr, PGSIZE, V2P(mem), PTE_W|PTE_U) < 0) {
        cprintf("Page fault error: Out of memory for the page table.\n");
        return;
    }
	cprintf("Page fault: Mapped page at addr=0x%x.\n", addr);
  }

  // Force process exit if it has been killed and is in user space.
  // (If it is still executing in the kernel, let it keep running
  // until it gets to the regular system call return.)
  if(proc && proc->killed && (tf->cs&3) == DPL_USER)
    exit();

  // Force process to give up CPU on clock tick.
  // If interrupts were on while locks held, would need to check nlock.
  if(proc && proc->state == RUNNING && tf->trapno == T_IRQ0+IRQ_TIMER)
    yield();

  // Check if the process has been killed since we yielded
  if(proc && proc->killed && (tf->cs&3) == DPL_USER)
    exit();
}
