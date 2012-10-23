#include <stdio.h>

int swap(int a, int b)
{
  //int c = a ^ b ^ a; // b 
  //int d = a ^ b ^ b; // a
  b = a ^ b;
  a = b ^ a;
  b = a ^ b;
  //b = b ^ a; //both are right

  printf("%d\n", a);
  printf("%d\n", b);
}

int main(void)
{
  swap(3, 5);
  swap(3, -5);

  return 0;
}
