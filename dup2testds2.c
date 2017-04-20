#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
main(int argc, char* argv[])
{
  int fd;

  // Ejemplo de dup2 con un fd incorrecto
  if (dup2 (-1,8) >= 0)
    printf (1, "dup2 no funciona con fd incorrecto.\n");

  // Ejemplo de dup2 con un fd no mapeado
  if (dup2 (6,8) >= 0)
    printf (1, "dup2 no funciona con fd inexistente.\n");

  // Ejemplo de dup2 con fd existente
  if (dup2 (1,4) != 4)
    printf (1, "dup2 no funciona con fd existente.\n");

  printf (4, "Este mensaje debe salir por terminal.\n");

  fd = open ("fichero_salida.txt", O_CREATE|O_RDWR);
  printf (fd, "Salida a fichero\n");

  if (dup2 (fd, 9) != 9)
    printf (1, "dup2 no funciona con fd existente (2).\n");

  printf (9, "Salida también a fichero.\n");
  close (9);

  if (dup2 (1, fd) != fd)
    printf (1, "dup2 no funciona con fd existente (3).\n");

  printf (fd, "Este mensaje debe salir por terminal.\n");
  close (fd);

  exit();
}
