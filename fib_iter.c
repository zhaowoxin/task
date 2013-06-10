#include <stdio.h>

int fib_iter(int i, int k, int count)
{
  //if (count == 0) {
  //return k;
  if (count == 2) {
    return i;
  } else {
    count --;
    //fib_iter(i + k, i, count);
    fib_iter(k, i + k, count);
  }
}

int fib(int n)
{
  //fib_iter(1, 0, n);
  fib_iter(1, 2, n);
}

int main(void)
{
  printf("%d\n", fib(9));

  return 0;
}
