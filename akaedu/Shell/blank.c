#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

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

void sethomedir(char *path)
{
    uid_t uid;
    struct passwd *wd;

    uid = getuid();
    printf("%d\n", uid);
    wd = getpwuid(uid);
    printf("%s\n", wd->pw_dir);
    strcpy(path, wd->pw_dir);
}

void changedir(char *cmd)
{
    char path[64];
    int i;
    char *des;
    
    getcwd(path, 64);
    printf("%s\n", path);
    /*
    if(*cmd == '.' && *(cmd + 1) == '.'){
        des = strrchr(path, '/');
        *des = '\0';
        if((cmd = strchr(cmd, '/')) != NULL)
            strcat(path, cmd);
    }
    else if(*cmd == '.'){
        if((cmd = strchr(cmd, '/')) < 0)
            strcat(path, cmd);
    }
    else */if(*cmd == '~'){
        cmd = strchr(cmd, '/');
        memset(path, '\0', 64);
        sethomedir(path);
    }
    else if(*cmd != '/'){
        for(i = 0; path[i] != '\0'; i++);
        path[i] = '/';
        path[i+1] = '\0';
        strcat(path, cmd);   
    }
    else{
        strcat(path, cmd);
    }
    printf("%s\n", path);
    if(chdir(path) < 0)
        perror("chdir error");
}

void skin(char *dir)
{
    printf("zhao@ubuntu:~%s$ ", dir);
}

int main(int argc, const char *argv[])
{
    char cmd[128], dir[32] = " "; 
    char *str;
    char *ccmd[64];
    int i, fd, flag;
    pid_t pid;

while(1)
{
    flag = 0;
    str = (char*)malloc(sizeof(char) * 128);
    skin(dir);
    //printf("zhao@ubuntu:~$ ");
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
        else if(strcmp(ccmd[0], "cd") == 0){
            flag = 1;
            changedir(ccmd[1]);
            printf("change success\n");
            strcat(dir, ccmd[1]);
            break;
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

