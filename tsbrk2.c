#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  char* a = sbrk (15000);

  sbrk (-15000);

  if (a != sbrk (15000))
  {
    printf (1, "sbrk() negativo falló.\n");
    exit();
  }

  printf (1, "Debe imprimir 1: %d.\n", ++a[500]);

  exit();
}
