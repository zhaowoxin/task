#include <stdio.h>

void print()
{
  static int i = 1;
  (i - 1001) && (printf("%d ", i++)) && (print(), 0);

  //(i - 1001) && (printf("%d ", i++)) && print(); 
  //error: void value not ignored as it ought to be
}

int main(void)
{
  print(1);
  printf("\n");

  return 0;
}
