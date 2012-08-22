#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    pid_t pid;
    char * ccmd[] = {"ls", "-l", "process.c", (char *)0};

    if((pid = fork()) < 0)
        fprintf(stderr, "fork error\n");
    else if(pid == 0){
        printf("child process\n");
        if(execv("/bin/ls", ccmd) < 0)
            fprintf(stderr, "exec error\n");
    }

    waitpid(pid, NULL, 0);

    return 0;
}
