#include <stdio.h>

int aaa(int a)
{
  printf("a is %d\n", a);

  return 0;
}

int bbb(int b)
{
  printf("b is %d\n", b + 1);    

  return 0;
}

int ccc(int c)
{
  printf("c is %d\n", c + 2);

  return 0;
}

struct funcptr
{
  int addr;
  int (*ptr)(int );
};

int main(void)
{
  int i;

  struct funcptr pptr[3] = {{1, aaa}, {2, bbb}, {3, ccc}};
  scanf("%d", &i);
  printf("addr is %d\n", i);
  pptr[i].ptr(i);

  return 0;
}
