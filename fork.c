#include <stdio.h>

/**********************************
 *          fork
 *       printf("-");
 *           /\
 *          /  \
 *         /    \
 *       fork  fork
 *  printf("-");  printf("--");
 *  
 *  
 *          fork
 *       printf("-");
 *           /\
 *          /  \
 *         /    \
 *       fork  fork
 *  printf("-");  printf("--");
 *
 ***********************************/

int main(void)
{
  int i;
  for (i = 0; i < 2; i++) 
  {
    fork();
    printf("-");
  }

  return 0;
}



