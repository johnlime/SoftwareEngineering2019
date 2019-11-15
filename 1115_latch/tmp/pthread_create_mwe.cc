#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "debug.h"

void *
worker(void *arg)
{
  char *str = (char *)arg;
  for (int i = 0; i < 10; i++) {
    puts(str);
    sleep(1);
  }
  return NULL;
}

int
main(void)
{
  pthread_t t1, t2;
  pthread_create(&t1, NULL, worker, (void *)"fizz"); 
  pthread_create(&t2, NULL, worker, (void *)"buzz"); 
  pthread_exit(NULL);
  puts("bye");

  return 0;
}
