#include <stdio.h>

typedef union {
  int a;
  float b;
} int2float;

int main(void)
{
  int2float i;
  float b = 3.0f;
  i.a = *(int *)&b;
  printf("%#x\n", i.a);
  printf("%f\n", i.b);

  return 0;
}
