#include <stdio.h>
#include <signal.h>

void (*ptr(int, void (*)(int)))(int);
void (*(*ptr2(int, void(*)(int))))(int); 
//void (**ptr2(int, void(*)(int)))(int); 
void* (*ptr3(int, void(*)(int)))(int); 
char (*(*x())[5])();
//char ((*y())[5])(); // wrong format
void def(int a)
{
  printf("callback function %d\n", a);
}

void (*(*ptr2(int abc, void(*def)(int))))(int) 
{
  printf("ptr2 %d\n", abc);
  def(5);
  printf("I am ptr2\n");
}
void (*(*ptr6(int abc, void* def)))(int) 
{
  printf("ptr6 %d\n", abc);
  void (*ghi)(int)= def;
  ghi(3);
  printf("hello world\n");    
}

int main(void)
{
  void (*(*ptr4)(int, void(*)(int)))(int); // wrong declare
  void (**(*ptr5)(int, void(*)(int)))(int); // wrong declare
  // function pointer ptr5 is equal that ptr2's declare
  //void (*(*ptr2(int, void(*)(int))))(int); 
  void (**(*ptr7)(int, void*))(int); // wrong declare

  ptr5 = ptr2;
  ptr5(3, def);
  ptr7 = ptr6;
  ptr7(100, def);
  ptr4 = signal;
  //printf("hello world\n");

  return 0;
}
