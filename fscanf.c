// how to use fscanf
#include <stdio.h>

int main(void)
{
  FILE *fp;
  int a, b;
  char c[8];
  int i = 0;

  fp = fopen("text", "r"); 
  while (1) {
    if (!feof(fp)) {
      printf("%d\n", i++);
      fscanf(fp, "%d %d %s\n", &a, &b, c);
      printf("%d %d %s\n", a, b, c);
    } else {
      break;
    }
  }

  return 0;
}
