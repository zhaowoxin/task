/*
 * Print numbers from 1 to 1000 without using any loop or conditional statements. 
 * Don't just write the printf() or cout statement 1000 times.
 */
#include <stdio.h>

#define NUM 1000
typedef int (*print)(int);

int print_end(int n)
{
  printf("1000\n");

  return 0;
}

int print_begin(int n)
{
  print func[2] = {print_begin, print_end};

  printf("%d\n", n++);
  func[n / NUM](n);
}

int main(void)
{
  print_begin(1);

  return 0;
}
