#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <atomic>
#include <thread>
#include <iostream>
#include "debug.h"

uint Counter = 0;
pthread_mutex_t Lock;
static constexpr uint NbThread = 10;
static constexpr uint NbLoop = 1000 * 1000 * 10;
static constexpr uint LockBit = 0x01;
static constexpr uint UnlockBit = 0x00;
std::atomic<uint> Mutex;

bool 
cas(uint *p, uint old_value, uint new_value)
{
  if (*p != old_value) return false;
  *p = new_value;
  return true;
}

uint
add(uint *p, uint add_value)
{
  bool done = false;
  uint counter;
  while (!done) {
    counter = *p;
    done = cas(p, counter, counter + add_value);
  }
  return counter + add_value;
}

void *
worker(void *arg)
{
  for (uint i = 0; i < NbLoop; i++) {
    add(&Counter, 1);
  }

  return NULL;
}

int
main(void)
{
  pthread_t thread[NbThread];
  if ((pthread_mutex_init(&Lock, NULL)) == -1) ERR;

  for (uint i = 0; i < NbThread; i++) {
    pthread_create(&thread[i], NULL, worker, NULL);
  }
  for (uint i = 0; i < NbThread; i++) {
    pthread_join(thread[i], NULL);
  }
  printf("Counter: %u (Ref. %u)\n", Counter, NbThread * NbLoop);

  return 0;
}
