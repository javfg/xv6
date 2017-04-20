#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


int 
main (int argc, char *argv[]) {
	int fd, newfd;
	newfd = 0;

	if (argc < 3) {
		printf(2, "Uso: dup2test fichero fichero2\n");
		exit();
	}

	if ((fd = open(argv[1], O_CREATE|O_RDWR)) < 0) {
		printf(2, "No se puede abrir '%s'.\n", argv[2]);
		exit();
	}

	if ((newfd = open(argv[2], O_CREATE|O_RDWR)) < 0) {
		printf(2, "No se puede abrir '%s'.\n", argv[3]);
		exit();
	}

	write(newfd, "SEGUNDO\n", 8);

    write(fd, "FD\n", 3);
    if (dup2(fd, newfd) < 0) {
        printf(2, "Error dup2.\n");
    }

    write(newfd, "NEWFD\n", 6);

    exit();
}
