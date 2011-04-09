#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "blank.h"

int main(void)
{
    char cmd[128];
    char *str;
    char **ccmd;
    int i;

    printf("zhaoyang@ubuntu:~$ ");
    gets(str);
    str = blank(cmd);
    //printf("%s\n", str);
    ccmd = arg(str);
    for(i = 0; ccmd[i] != NULL; i++) {
        printf("%s\n", ccmd[i]);
    }

    return 0;

#if 0
    if((pid = fork()) < 0){
        fprintf(stderr, "fork error\n");
    }else if(pid == 0){
        execv("/bin", ccmd);
    }
#endif
}
