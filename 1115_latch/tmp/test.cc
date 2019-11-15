#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "debug.h"

int Value_x = 0;
int Value_y = 0;

void *
worker_1(void *arg)
{
  printf("x = %d\n", Value_x);
  Value_x = 1;
  return NULL;
}

void *
worker_2(void *arg)
{
  printf("y = %d\n", Value_y);
  Value_y = 1;
  return NULL;
}

int
main(void)
{
  pthread_t thread[2];
  int ret;
  ret = pthread_create(&thread[0], NULL, worker_1, NULL); if (ret == -1) ERR;
  ret = pthread_create(&thread[1], NULL, worker_2, NULL); if (ret == -1) ERR;
  pthread_join(thread[1], NULL);
  pthread_join(thread[0], NULL);
  
  return 0;
}
