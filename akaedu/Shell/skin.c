#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    char cmd[128];
    int pid, i = 1;
    char *ccmd[64];

    while(1){
        printf("propt->");
        scanf("%s", cmd);
        cmd = blank(cmd);
        ccmd[0] = cmd;
        while(*cmd != '\0'){
            if(*cmd == ' '){
                *cmd++ = '\0';
                ccmd[i++] = cmd;
            }
        }
        if((pid = fork()) < 0){
            fprintf(stderr, "fork error\n");
        }else if(pid == 0){
            execv("/bin", argv);
        }
    }

    return 0;
}
