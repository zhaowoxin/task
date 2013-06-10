#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * When I was a child, my mother told me a game,
 * it confused me at the following days.
 * The rules is like that 
 *   There are 13 pokers from A~K.
 *   first you put the bottom poker to the top
 *   extract the second poker. It is A
 *   repeat first step
 *   the forth poker is 2
 *   ...
 *   the last poler is K
 *                               2012.9.24
 */

/*
 * ---------------------------
 * | |1| |2| |3| |4| |5| |6| |
 * ---------------------------
 * Put the left numbers in the blanks.
 * Look out that if you pass the 13th blank
 * You should not pass the next one blank(1st blank)
 */

typedef struct pok
{
  int num;
  int flag;
} pk;

int main(void)
{
  pk poke[13];
  memset(poke, 0, sizeof(poke));
  int model[13] = {1, 2, 3, 4, 5, 
                   6, 7, 8, 9, 10,
                   11, 12, 13};

  int i = 13, tmp = 1, j = 0, flag = 0;
  while(i != 0) {
    if (poke[tmp%13].flag == 0 && flag == 0) {
      if (j < sizeof(model)/sizeof(int))
        poke[tmp%13].num = model[j++];
      else {
        printf("error\n");
        exit(1);
      }
      poke[tmp].flag = 1;
      i --;
      tmp += 2;
      tmp %= 13;
      if (tmp == 2) //make the 1th blank in this if, not passed 
        flag = 1;
    } else if (poke[tmp%13].flag == 0 && flag == 1){
      while (poke[++tmp%13].flag == 1);
      if (j < sizeof(model)/sizeof(int))
        poke[tmp%13].num = model[j++];
      else {
        printf("error\n");
        exit(1);
      }
      poke[tmp].flag = 1;
      i --;
      tmp %= 13;
    } else {
      tmp ++;
      tmp %= 13;
    }
  }

  printf("The number consequence is: \n");
  for(i = 0; i < 13; i++) {
    printf("%d ", poke[i].num);
  }
  puts("\n");

  return 0;
}
