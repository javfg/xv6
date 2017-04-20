#include "types.h"
#include "user.h"

int recursive(int v)
{
  printf (1, ".");
  if (v > 0)
    return recursive (++v);
  return 0;
}


int
main(int argc, char *argv[])
{
  int i = 1;

  // Llamar recursivamente a recursive
  printf (1, ": %d\n", recursive (i));

  exit();
}
