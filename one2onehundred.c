/*
 * Print sum from 1 to 100 without using any loop or conditional
 * statements. Don't just write the printf() or cout statement 1000 times.
 */

#include <stdio.h>

typedef int (*fun)(int);

int solution3_f1(int i) 
{
  return 0;
}

int solution3_f2(int i)
{
  fun f[2]={solution3_f1, solution3_f2}; 
  return i+f[!!i](i-1);
}

int main(void)
{
  int sum = solution3_f2(100);
  printf("%d\n", sum); // 5050

  return 0;
}
