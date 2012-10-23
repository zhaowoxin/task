#include <stdio.h>

FILE *fp;
int data = 5;
const int data2 = 7;
int array[5] = {1, 2, 3, 4, 5};

void begopen()
{
  fopen("aaa", "w");
  fprintf(fp, "hello world");
}

void endclose()
{
  fclose(fp);
}
    
int main(void)
{
  const int a=5;
  static int data3 = 8;
  int data4;
  int data5;
  begopen();
  endclose();
  data = 8;
  data3 = data;
  data4 = a;
  data5 = array[3];

  return 0;
}

