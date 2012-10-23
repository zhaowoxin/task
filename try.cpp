#include <stdio.h>

class A;
A* Array[2];

class A
{
  public:
    virtual int Sum (int n) { return 0; }
};

class B: public A
{
  public:
    virtual int Sum (int n) { return Array[!!n]->Sum(n-1)+n; }
};

int solution2_Sum(int n)
{
  A a;
  B b;
  Array[0] = &a;
  Array[1] = &b;

  int value = Array[1]->Sum(n);
  //int value = Array[0]->Sum(n);
  printf("%d\n", value);

  return value;
}

int main(void)
{
  solution2_Sum(100);

  return 0;
}
