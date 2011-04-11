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
        printf("parents process\n");
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        write(pipefd[1], buf, strlen(buf));

        /*
        }else{

        }
        */
    }else{           
            printf("child process\n");
            close(pipefd[1]);
            dup2(pipefd[0], STDIN_FILENO);
            read(pipefd[0], buf, strlen(buf));    
            waitpid(pid, NULL, 0);
    }
    
    return 0;
}
