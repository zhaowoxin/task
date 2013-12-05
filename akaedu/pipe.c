#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, const char *argv[])
{
  int pipefd[2];
  pid_t pid;
  char buf[64];

  if(pipe(pipefd) < 0)
    fprintf(stderr, "pipe error\n");
  if((pid = fork()) < 0){
    fprintf(stderr, "fork error\n");
    exit(1);
  }else if(pid == 0){
    close(pipefd[0]);
    read(STDIN_FILENO, buf, 64);
    write(pipefd[1], buf, 64);
    close(pipefd[1]);

  }else{           
    waitpid(pid, NULL, 0);
    printf("parent process\n");
    close(pipefd[1]);
    //dup2(STDIN_FILENO,pipefd[1]);
    read(pipefd[0], buf, 64);    
    printf("buf is \"%s\"\n", buf);
    close(pipefd[0]);
  }

  return 0;
}
