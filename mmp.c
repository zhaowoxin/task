#define _GNU_SOURCE
// This macro is fatal by `remmap
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/mman.h>
#include <unistd.h>
#include <stdarg.h>

#define MAX_LEN 65536 << 8

int length = 0;
int fd;
void *dest;

void init()
{
  char name[128];
  struct stat st;
  int i = 5;

  sprintf(name, "libabc.so_%d.ll", i);
  fd = open(name, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
  write(fd, ";test\n", 6);
  //stat(name, &st);
  //length = st.st_size;
  ftruncate(fd, MAX_LEN);
  if ((dest = mmap(NULL, MAX_LEN, PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    printf("ERROR: %s\n", strerror(errno));
  }
}

void llvm_outs(char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  length += vsprintf(dest + length, fmt, ap);
  va_end(ap);
}

void fini()
{
  ftruncate(fd, length);
  msync(dest, MAX_LEN, MS_ASYNC);
  munmap(dest, MAX_LEN);
  close(fd);
}

int main(void)
{
  int a = 156, b = 2556;
  int i = 0;

  init();
  for (i = 0; i < 30000; i++){
    llvm_outs("%%tmp_%d = lsr i32, %d\n", i, b);
    llvm_outs("%%tmp_%d = lsr i32, %d\n", a + 1, i);
  }
  fini();

  return 0;
}
