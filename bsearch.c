#include <stdio.h>
#include <stdlib.h>

int comp(int *a, int *b)
{
  printf("*a is :%d, *b is :%d\n", *a, *b);
  printf("*b + 1 is %d\n", *(b+1));
  // this condition return the nearest value of the key
  if (*a  > *(b - 1) + ((*b - *(b - 1)) / 2) &&  *a < * b + ((*(b+1) - *b) / 2))
  // this condition return the previous of the key value
  //if (*a > *b && *a < *(b+1))
    return 0;
  else 
    return *a - *b;
}

int main(void)
{
  // sorted
  int a[] = {1, 10, 20, 30, 40, 50, 70};
  int len = sizeof(a) / sizeof (int);
  int *res;
  int key = 30;
  if (key > a[len - 1] || key < a[0])
    return -1;
  res = bsearch(&key, a, 6, sizeof(int), comp);
  printf("res :%d\n", *res);

  return 0;
}
