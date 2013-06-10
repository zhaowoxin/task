/*
 * Fibonacci recursion version
 */
#include <stdio.h>

int fib(int num)
{
  if (num == 2)
    return 1;
  else if (num == 3)
    return 2;
  else {
    return (fib(num - 1) + fib(num - 2));
  }
}

int main(void)
{
  printf("%d\n", fib(8));

  return 0;
}
