#include <stdio.h>
#include <pthread.h>
pthread_key_t pkey;

void function_(int num) 
{
  if (num == 100)
    printf("it is in first thread\n");
  else if (num == 200)
    printf("it is in second thread\n");
}

void function(void)
{
  int *tmp = (int *)pthread_getspecific(pkey);
  printf("%d is runing in %s\n", *tmp, __FUNCTION__);
  function_(*tmp);
}

void *p_function(void *arg)
{
  pthread_setspecific(pkey, arg);

  int *tmp = (int *)pthread_getspecific(pkey);
  printf("%d is runing in %s\n", *tmp, __FUNCTION__);
  *tmp = *tmp * 100;
  function();

  return (void*)0;
}

int main(void)
{
  int a = 1, b = 2;
  pthread_t tid, tid_;

  pthread_key_create(&pkey, NULL);
  pthread_create(&tid, NULL, p_function, &a);
  pthread_create(&tid_, NULL, p_function, &b);
  pthread_join(tid, NULL);
  pthread_join(tid_, NULL);

  return 0;
}
