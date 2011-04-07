#include <stdio.h>
#include <stdlib.h>

char* blank(char *cmd)
{
    char *str, *buf;

    str = (char*)malloc(sizeof(char) * 128);
    buf = str;
    if(*cmd == ' '){
        fprintf(stderr,"command error\n");
        exit(1);
    }
    while(*cmd != '\0'){
        if((*cmd == ' ' && *(cmd + 1) != ' ') || *cmd != ' '){
            *str++ = *cmd;
        }
        cmd++;
    }
    *str = '\0';

    return str;
    //printf("%s\n", buf);
}

int main(int argc, const char *argv[])
{
    char cmd[128] = "ls    -l   a";
    blank(cmd);

    return 0;
}
