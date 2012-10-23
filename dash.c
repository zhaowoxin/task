#include <stdio.h>

int main(void)
{
  int i;
  for(i = 1; i < 10; i ++)
    printf("%.*s", i, "---------------");

  return i;
}
