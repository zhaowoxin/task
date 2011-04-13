#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, const char *argv[])
{
    int pipefd[2];
    pid_t pid;
    char buf[64] = "hello world";

    if(pipe(pipefd) < 0)
        fprintf(stderr, "pipe error\n");
    if((pid = fork()) < 0){
        fprintf(stderr, "fork error\n");
        exit(1);
    }else if(pid == 0){
        /*
        if((pid = fork()) < 0){
            fprintf(stderr, "fork error\n");
            exit(1);
        }else if(pid == 0){
        */
        printf("child\n");
        close(pipefd[1]);
        dup2(STDIN_FILENO, pipefd[0]);
        read(STDIN_FILENO, buf, 64);

        /*
        }else{

        }
        */
    }else{           
            waitpid(pid, NULL, 0);
            printf("parent process\n");
            close(pipefd[0]);
            dup2(STDIN_FILENO,pipefd[1]);
            write(pipefd[1], buf, 64);    
    }
    
    return 0;
}
