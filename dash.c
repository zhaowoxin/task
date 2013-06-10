#include <stdio.h>

int main(void)
{
  int i;
  for(i = 1; i < 10; i ++)
    printf("%.*s\n", i, "---------------");

  return i;
}
