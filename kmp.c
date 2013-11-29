// KMP algrithm
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

void build_kmp_table(char *sub, int *sub_table)
{
  sub_table[0] = 0;
  int i = 1, j = 0;

  while (sub[i]) {
    if (sub[i] == sub[j])  {
      sub_table[i] = sub_table[i - 1] + 1;
      j++;
      i++;
    } else {
      sub_table[i] = 0;
      j = 0;
      i++;
    }
  }
}

int compare_sub_str(char *str, char *sub, int *sub_table)
{
  char *total = str;
  char *tmp = sub;
  int i = -1, j = 0;
  int flag = 0;

  while (*total) {
    if (*tmp == *total) {
      total++;
      tmp++;
      i++;
      j++;
      flag = 1;
      if (*tmp == '\0') {
        return total - str;
      }
    } else {
      if (flag == 1 || sub != tmp) {
        tmp -= j - sub_table[i];
        i = tmp - sub - 1;
        j = tmp - sub;
        flag = 0;
      } else {
        total++;
        tmp = sub;
        j = 0;
        i = -1;
      }
    }
  }

  return -1;
}

int main(void)
{
  char *str = "BBC ABCDAB ABCDABCDABDE";
  char *sub = "ABCDABD";
  //char *sub = "ABDEFGHI";
  int *sub_table = (int *)malloc(sizeof(int) * strlen(sub));
  memset (sub_table, 0, sizeof(int)*strlen(sub));

  build_kmp_table(sub, sub_table);
#if 1
  int i;
  for (i = 0; i < strlen(sub); i++) 
  {
    printf("%d ", sub_table[i]);
  }
  puts("");
#endif
  int ret = compare_sub_str(str, sub, sub_table);
  printf("ret is %d\n", ret);
  

  return 0;
}
