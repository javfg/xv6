#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"


int main (int argc, char *argv[]) {
  char *a;
  int i;

  printf(1, "RESERVO\n");
  a = sbrk(32);
  for (i = 0; i < 32; i++)
    a[i] = 'a';
  printf(1, "%s\n", a);

  printf(1, "LIBERO\n");
  sbrk(-4000);

  printf(1, "RESERVO\n");
  sbrk(32);
  for (i = 0; i < 32; i++)
    a[i] = 'b';
  printf(1, "%s\n", a);

  exit();
}
