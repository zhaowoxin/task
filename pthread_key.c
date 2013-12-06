#include <stdio.h>
#include <pthread.h>

pthread_key_t key;
int global;

void get_global()
{
  //int *iptr = pthread_getspecific(key);
  //printf("number is %d\n", *iptr);
  printf("%d\n", global);
}

void *threadfunc(void *arg)
{
  int i = (int)arg;
  global = i;
  //pthread_setspecific(key, &global);
  get_global();
}

int main(void)
{
  pthread_t tid[3];
  int i;

  pthread_key_create(&key, NULL);
  for (i = 0; i < 3; i++) 
  {
    pthread_create(&tid[i], NULL, threadfunc, (void *)i);
  }

  for (i = 0; i < 3; i++) 
  {
    pthread_join(tid[i], NULL);
  }
  pthread_key_delete(key);

  return 0;
}
