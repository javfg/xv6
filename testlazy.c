#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"


int 
main (int argc, char *argv[]) {
  char *a;

  a = sbrk(400000000);

  int i;
  for (i = 0; i < 400000000; i++)
    a[i] = 'a';

  exit();
}
