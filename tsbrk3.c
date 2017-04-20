#include "types.h"
#include "fcntl.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int fh = open ("README", O_RDONLY);

  char* a = sbrk (15000);

  read (fh, a+500, 50);

  // Debe imprimir los 50 primeros caracteres de README
  printf (1, "Debe imprimir los 50 primeros caracteres de README:\n");
  printf (1, "%s\n", a+500);

  close (fh);

  exit();
}
