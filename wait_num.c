#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
  int arr[10];
  int i, j = 1;
  memset(arr, 0, sizeof(arr));
  while (1) {
    for (i = 0; i < 10; i++) {
      if (arr[i] == 0) {
        arr[i] = j;
        j++;
        break;
      }     
    }
    if (i == 9)
      break;

    for (i = 0; i < 10; i++) {
      if (arr[i] != 0) {
        arr[i]--;
      } 
    }
  }

  printf("Max number is %d\n", j);

  return 0;
}
