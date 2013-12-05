#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define _TIME(time) ((time) * 100000)

//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
typedef struct list {
  int id;
  int is_run;
  int run_time;
  pthread_t node_tid;
  struct list *next;
} node;

typedef struct backup {
  int time; 
  struct backup *next;
}backup;
typedef backup *bakup_list;

void mklist(node **list, int num)
{
  int i;
  (*list) = (node *)malloc(sizeof(node));
  (*list)->id = 0;
  (*list)->is_run = 0;
  (*list)->next = NULL;
  node *bak = *list;
  for(i = 1; i < num; i++) {
    bak->next = (node *)malloc(sizeof(node));
    bak->next->id = i;
    bak->next->is_run = 0;
    bak->next->next = NULL;
    bak = bak->next;
  }
  bak->next = *list;
}

void prlist(node *list, int value)
{
  printf("list id is %d\n", list->id);
  list = list->next;
  while (list->id != value) {
    printf("list id is %d\n", list->id);
    list = list->next;
  }
}

int lenlist(node *list, int value)
{
  if (!list) {
    return 0;
  } else if (!list->next) {
    return 1;
  } else {
    int i = 1;
    list = list->next;
    while (list->id != value) {
      i++;
      list = list->next;
    }
    return i;
  }
}

// pos is from 0, id is unique;
node *inslist(node *list, int value, int pos)
{
  int i;
  node *bak = list, *bak2;
  if (list) {
    if (pos > 0 && pos < lenlist(list, list->id)) {
      node *tmp = (node *) malloc (sizeof(node));
      tmp->id = value;
      for (i = 0; i < pos; i++)
        bak  = bak->next;
      bak2 = bak->next;
      bak->next = tmp;
      tmp->next = bak2;
    } else if (pos == 0){
      node *tmp = (node *) malloc (sizeof(node));
      tmp->id = value;
      list = list->next;
      while (list->next->id != bak->id) {
        list = list->next;
      }
      list->next = tmp;
      tmp->next = bak;
      list = tmp;
    } else {
      printf("error !!!\n");
      printf("==============\n");
    }

    return list;
  }
}

node *del_list_by_pos(node *list, int pos)
{
  int i;
  node *bak = list, *bak2;
  int len = lenlist(list, list->id);

  if (list) {
    if (pos == 0) {
      list = list->next;
      while (list->next->id != bak->id) {
        list = list->next;
      }
      bak2 = bak->next;
      free(bak);
      list->next = bak2;
      list = bak2;
    } else if (pos > 0 && pos < len) {
      for (i = 0; i < pos - 1; i++) {
        bak = bak->next;
      }
      bak2 = bak->next->next;
      free(bak->next);
      bak->next = bak2;
    } 
  }

  return list;
}

node *del_list_by_value(node *list, int value)
{
  // TODO
}

int i = 1;
void *do_nothing(void *n)
{
  node *bak = (void *)n;
  printf("in do_nothing wait for %d time, id is %#lx\n", (int)bak->run_time, bak->node_tid);
  bak->is_run = 1;
  usleep(_TIME((int)bak->run_time));
  printf("===========the %d thread is over=======id is %#lx=====\n", i, bak->node_tid);
  bak->is_run = 0;
  i++;

  return (void *)0;
}

int schedule(node *head, int time)
{
   struct timespec t_start;
   struct timespec t_end;
   int len = lenlist(head, head->id); 
   int ret;
   int k = 0;
   node *bak = head;
   while (1) {
     clock_gettime(CLOCK_REALTIME, &t_start);
     if (bak->is_run == 1) {
       printf("next node %d\n", k++);
       bak = bak->next;
       if(bak->id == head->id) {
         clock_gettime(CLOCK_REALTIME, &t_end);
         printf("The while loop spend %ld second and %ld nano-second\n",
             t_end.tv_sec - t_start.tv_sec, t_end.tv_nsec - t_start.tv_nsec);
         return 1;
       }
     } else {
       bak->run_time = time;
       ret = pthread_create(&bak->node_tid, NULL, do_nothing, (void *)bak);  
       if (ret == 0) {
         //bak->is_run = 1;
         clock_gettime(CLOCK_REALTIME, &t_end);
         printf("The while loop spend %ld second and %ld nano-second\n",
             t_end.tv_sec - t_start.tv_sec, t_end.tv_nsec - t_start.tv_nsec);
         printf("++++++++++++++the %dth thread++++id %#lx++++++++++++\n", time, bak->node_tid);
         return 0;
       } 
     }
   }
}

void *task_algorithm(void* hd)
{
  node *head = (node *)hd;
  int n = 1, ret;
  while (1) {
    usleep(_TIME(1));
    ret = schedule(head, n);
    if (ret == 1) {
      printf("==========pool is full===================\n");
      exit(1);
      // add it to the linked-list
      //add_into_backup_list();
    } else if (ret == 0){
    }
    n++;
    //n--;
    if (n == 20) {
      printf("task over\n");
      exit(1);
    }
  }
}

void main_schd(node *head)
{
  pthread_t tid;
  int ret;
  ret = pthread_create(&tid, NULL, 
      task_algorithm, (void *)head);
  if (ret == 0) {
    printf("successful\n");
  } else {
    printf("failed\n");
  }
  pthread_join(tid, NULL);
}

int main(void)
{
  node *head;
  mklist(&head, 3);
  prlist(head, head->id);
  printf("=============\n");
  main_schd(head);

  return 0;
}
