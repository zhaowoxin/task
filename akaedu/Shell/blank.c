#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void blank(char *cmd, char *str)
{
    char *buf;

    buf = str;
    if(*cmd == ' '){
        fprintf(stderr,"command error\n");
        exit(1);
    }
    while(*cmd != '\0'){
        if((*cmd == ' ' && *(cmd + 1) != ' ') || *cmd != ' '){
            *buf++ = *cmd;
        }
        cmd++;
    }
    *buf = '\0';
//    printf("%s\n", str);
}

void arg(char *cmd, char *ccmd[])
{
    int i = 1;

    ccmd[0] = cmd;
    while(*cmd != '\0'){
        if(*cmd == ' '){
            *cmd = '\0';
            ccmd[i++] = ++cmd;
        }
        else
            cmd++;
    }
    ccmd[i] = NULL;
}

int main(int argc, const char *argv[])
{
    char cmd[128]; 
    char *str;
    char *ccmd[64];
    int i, fd, flag = 0;
    pid_t pid;

while(1)
{
    str = (char*)malloc(sizeof(char) * 128);
    printf("zhao@ubuntu:~$ ");
    gets(cmd);
    blank(cmd, str);
    arg(str, ccmd);
    for(i = 0; ccmd[i] != NULL; i++){
        if(*ccmd[i] == '>'){
            ccmd[i] = NULL;
            flag = 1;
            if((pid = fork()) < 0){
                fprintf(stderr, "fork error\n");
            }    
            else if(pid == 0){
                if((fd = open(ccmd[i + 1], O_RDWR | O_CREAT | O_TRUNC)) < 0)
                    fprintf(stderr, "open error\n");
                fchmod(fd, 777);
                dup2(fd, STDOUT_FILENO);
                if(execvp(ccmd[0], ccmd) < 0)
                    fprintf(stderr, "exec error\n");
                close(fd);
            }else
                waitpid(pid, NULL, 0);
        }
        else if(*ccmd[i] == '<'){
            ccmd[i] = NULL;
            flag = 1;
            if((pid = fork()) < 0){
                fprintf(stderr, "fork error\n");
            }    
            else if(pid == 0){
                if((fd = open(ccmd[i + 1], O_RDONLY)) < 0)
                    fprintf(stderr, "open error\n");
                dup2(fd, STDIN_FILENO);
                if(execvp(ccmd[0], ccmd) < 0)
                    fprintf(stderr, "exec error\n");
                close(fd);
            }else
                waitpid(pid, NULL, 0);
        }
    }
    if(flag == 0){
        if((pid = fork()) < 0)
            fprintf(stderr,"fork error\n");
        else if(pid == 0){
            //printf("child process\n");
            if(execvp(ccmd[0], ccmd) < 0)
                fprintf(stderr, "exec error\n");
        }
        else {
           // printf("parent process\n");
            waitpid(pid, NULL, 0);
        }
    } 

    free(str);
}
    return 0;
}

