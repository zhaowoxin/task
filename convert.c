/* * 
 * This is just a simple case that distingwish the difference between 
 * double b = (double)a; //should be 5.0
 * and 
 * double c = *(double *)&a; //should be unknow
 * the first one cast int type to double,
 * but the true value in memory should be modified.
 * the second one regard variable a (5) as a true memory value,
 * CPU load this value in memory and convert it to its true double value
 * Maybe my English is tooooo poor, but if you compile it by yourself
 * the result should be clearly.
 *                                 2012.9.19
 * */

#include <stdio.h>

int main(void)
{
  int a = 5;

  double b = (double)a;
  printf("%e\n", b);

  double c = *(double *)&a;
  printf("should be not 5 %e\n", c);

  double d = *(double *)&b;
  printf("should be 5 %e\n", d);

  int e = *(int *)&b;
  printf("%#x\n", e);

  return 0;
}
