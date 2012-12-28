#define _GNU_SOURCE
// This macro is fatal
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/mman.h>
#include <unistd.h>

int main(void)
{
  int abc[10];
  void *dest;
  struct stat st;

  int fd = open("111", O_RDWR);
  stat("./111", &st);
  int length = st.st_size;
  printf("length is %d\n", length);

  if ((dest = mmap(NULL, length, PROT_READ, MAP_SHARED, fd, 0)) == MAP_FAILED) {
    printf("ERROR: %s\n", strerror(errno));
  }
  void *dest2 = mremap((void *)dest, length, length + 1, MREMAP_MAYMOVE);
  if (dest2 == MAP_FAILED) {
    printf("ERROR: %s\n", strerror(errno));
  }
  if (msync(dest2, length * 2, MS_SYNC) == -1) {
    printf("ERROR: %s\n", strerror(errno));
  }

  printf("%p\n%s\n", dest, (char *)dest);
  printf("-----------------------\n");
  printf("%p\n%s\n", dest2, (char *)dest2);
  munmap(dest2, length);

  return 0;
}
