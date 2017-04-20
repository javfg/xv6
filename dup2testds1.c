#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define READ_END 0
#define WRITE_END 1

int 
main(int argc, char* argv[]) 
{
    int pid;
    int fd[2];
    char* lsargv[] = {"ls",0};
    char* grepargv[] = {"grep","README", 0};

    pipe(fd);
    pid = fork();

    if(pid==0)
    {
        printf(2, "Soy el hijo que ejecuta ls\n");
        dup2(fd[WRITE_END], 1);
        close(fd[READ_END]);
        if(exec("ls", lsargv) < 0){
          printf(2, "ls failed\n");
          exit();
        }
    }
    printf(2, "Soy el padre que ejecuta grep\n");
    dup2(fd[READ_END], 0);
    close(fd[WRITE_END]);
    if(exec("grep", grepargv) < 0){
      printf(2, "grep failed\n");
      exit();
    }
    return 0;
}
