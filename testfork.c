#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char* argv[]) {
    sbrk(8192);
    int pid = fork();

    if(pid == 0) {
        printf(2, "Soy el hijo.\n");
        sleep(50);
        exit();
    }

    printf(2, "Soy el padre.\n");
    wait();
    exit();

    return 0;
}
