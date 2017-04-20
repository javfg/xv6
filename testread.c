#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[]) {
  int fd;

  fd = open("fichero_salida.txt", O_CREATE|O_RDWR);
  printf(fd, "Salida a fichero\n");
  close(fd);

  char *a;
  a = sbrk(32);
  fd = open("fichero_salida.txt", O_RDWR);

  read(fd, a, 17);

  printf(1, "CONTENIDO: %s\n", a);

  exit();
}
