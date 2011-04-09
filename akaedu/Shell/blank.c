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

    return buf;
    //printf("%s\n", buf);
}

char ** arg(char *cmd)
{
    char *ccmd[64];
    int i = 1;

    //printf("propt->");
    //scanf("%s", cmd);
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
    
    return ccmd;
}

#if 0
int main(int argc, const char *argv[])
{
    char cmd[128] = "ls -l a";
    char *str;
    char **ccmd;
    int i;

    str = blank(cmd);
    printf("%s\n", str);
    ccmd = arg(str);
    for(i = 0; ccmd[i] != NULL; i++) {
        printf("%s\n", ccmd[i]);
    }

    return 0;

}
#endif

