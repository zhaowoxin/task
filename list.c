#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

#define _TIME(time) ((time) * 100)
pthread_mutex_t mutex, mutex2;

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
typedef backup *bakup_ptr;
bakup_ptr back_list_head;

void mklist(node **list, int num)
{
  int i;
  (*list) = (node *)malloc(sizeof(node));
  node *bak = *list;
  for(i = 0; i < num; i++) {
    (*list)->next = (node *)malloc(sizeof(node));
    (*list)->id = i;
    (*list)->is_run = 0;
    (*list) = (*list)->next;
  }
  *list = (*list)->next = bak;
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

int iter;
void del_from_backup_list(void)
{
  if (back_list_head->next) {
    bakup_ptr bak = back_list_head->next;   
    printf("delete from backup list, %d\n", iter);
    iter--;
    free(back_list_head);
    back_list_head = bak;
  } else {
    printf("--------------------is the last list--------------------\n");
    back_list_head->time = -1;
    back_list_head->next = NULL;
    iter--;
  }
}

void add_into_backup_list(int time)
{
  // insert to approprite pos. according to time.
  bakup_ptr bak = back_list_head;
  bakup_ptr new = (bakup_ptr) malloc (sizeof(struct backup));
  if (new != NULL) {
    for (; bak->next != NULL; bak = bak->next);
    new->time = time;
    new->next = NULL;
    bak->next = new;
    iter++;
    printf("add into backup list, %d\n", iter);
  }
}

int i = 0;
void *do_nothing(void *n)
{
  node *bak = (void *)n;
  bak->is_run = 1;
  pthread_mutex_lock(&mutex2);
  usleep(_TIME((int)bak->run_time));
  i++;
  if (back_list_head->time != -1) {
    printf("iter is %d\n", iter);
    del_from_backup_list();
  }
  pthread_mutex_unlock(&mutex2);
  bak->is_run = 0;
  printf("========the %d thread is over use %p poll==============\n", i, bak);

  return (void *)0;
}

int schedule(node *head, int time)
{
  //int len = lenlist(head, head->id); 
  int ret;
  int k = 0;
  node *bak = head;
  while (1) {
    if (bak->is_run == 1) {
      printf("next node %d, %d\n", k++, bak->is_run);
      bak = bak->next;
      if(bak->id == head->id) {
        //exit(1);
        return 1;
      }
    } else {
      printf("poll addr is %p, %d\n", bak, bak->is_run);
      if (back_list_head->time != -1) {
        printf("fetch the back_up list %d\n", back_list_head->time);
        printf("add the current %d\n", time);
        add_into_backup_list(time);
        bak->run_time = back_list_head->time;
      } else if (time == 0) {
        bak->run_time = back_list_head->time;
      } else {
        bak->run_time = time;
      }
      ret = pthread_create(&bak->node_tid, NULL, do_nothing, (void *)bak);  
      if (ret == 0) {
        //printf("the %dth thread\n", i);
        return 0;
      } 
    }
  }
}

void *task_algorithm(void* hd)
{
  node *head = (node *)hd;
  int k = 0;
  bakup_ptr back_list = (bakup_ptr)malloc(sizeof(struct backup));
  if (back_list == NULL) {
    printf("malloc error\n");
    exit (1);
  }

  back_list_head = back_list;
  //init backup link-list
  memset(back_list, -1, sizeof(struct backup));

  int n = 1, ret;
  while (1) {
    printf("call main thread callback function\n");
    usleep(_TIME(1));
    ret = schedule(head, n);
    if (ret == 1) {
      //add it to the linked-list
      printf("==========poll is full===================\n");
      if (back_list_head->time == -1) {
        iter ++;
        back_list_head->time = n;
        back_list_head->next = NULL;
        printf("add first time %d\n", n);
        exit(1);
      } else {
        printf("add not first %d\n", n);
        add_into_backup_list(n);
        printf("list is %d\n", ++k);
      }
    } else if (ret == 0){
      printf("thread is running\n");
    }
    n++;
    //n--;
    printf("+++++++++++++++++n is %d++++++++++++++++++++++\n", n);
    if (n == 20) {
      printf("echo to 100, iter is %d\n", iter);
      //exit(1);
      printf("begin to collect the rest one\n");
      node *lookup = head;
      for (; lookup->next->id != head->id; lookup = lookup->next) {
        printf("next one\n");
        if (lookup->is_run == 1) {
          printf("wait the rest threads\n");
          pthread_join(lookup->node_tid, NULL);
        }
      }
      //printf("wait the rest tasks\n");
      //while (iter != 0) {
        //printf("iter is %d\n", iter);
        //ret = schedule(head, 0);
      //} 


      // TODO: Should be think more carefully 
      //while(1) {
        //ret = schedule(head, 0);
        //if (ret == 1)
          //continue;
        //if (back_list_head->time == -1) {
          //break;
        //}
        //}
      free(back_list);
      printf("task over\n");
      break;
    }
  }
}

void main_schd(node *head)
{
  pthread_t tid;
  int ret;
  printf("call main_schd function\n");
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
  mklist(&head, 10);
  //prlist(head, head->id);
  printf("=============\n");
  main_schd(head);
  //head = inslist(head, 11, 8);
  //prlist(head, head->id);
  //printf("=============\n");
  //head = inslist(head, 15, 0);
  //prlist(head, head->id);
  //printf("=============\n");
  //head = inslist(head, 15, 20);
  //prlist(head, head->id);
  //printf("=============\n");
  //head = del_list_by_pos(head, 3);
  //prlist(head, head->id);
  //printf("=============\n");
  //head = del_list_by_pos(head, 0);
  //prlist(head, head->id);
  //printf("=============\n");

  return 0;
}
