/* 
 * just write a program about the disassembly 
 * that implement swaping 2 numbers
 */
#include <stdio.h>

#if 1
int swap2(int a, int b)
{
  //register unsigned int *addr_b, *addr_a;
  __asm("movl %0,%%eax\n"
        "leal %1,%%ebx\n"
        "leal %0,%%ecx\n"
        "movl %1,%%edx\n"
        "movl %%edx,%0\n"
        "movl %%eax,%1"
        ::"m" (a), "m" (b));

  printf("%d, %d\n", a, b);
}
#endif

int swap(int a, int b)
{
  //register unsigned int *addr_b, *addr_a;
  __asm("movl %%eax, %%ecx\n"
        "movl %%ebx, %%eax\n"
        "movl %%ecx, %%ebx\n"
        :"=a" (a), "=b" (b):"a" (a), "b" (b));

  printf("%d, %d\n", a, b);
}
int main(void)
{
  int c = swap(3, 4);
  int d = swap2(3, 4);
  printf("%d %d\n", c, d);

  return 0;
}
