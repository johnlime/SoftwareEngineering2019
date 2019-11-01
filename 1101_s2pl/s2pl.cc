#include "concurrency.h"

DATA DataObj[MAX_OBJ];

void
my_sort(int access[])
{
}

static void *
worker(void *arg)
{
  int access[MAX_OPERATION];
  for (int i = 0; i < MAX_OPERATION; i++) {
    access[i] = rand() % MAX_OBJ;
  }

  // Sort
  my_sort(access);

  /* Growing Phase */
  for (int i = 0; i < MAX_OPERATION; i++) {
		lock(access[i]);
  }

  for (int i = 0; i < MAX_OPERATION; i++) {
		task_alpha(i);
  }
	
	/* Shrinking Phase */
  for (int i = 0; i < MAX_OPERATION; i++) {
		unlock(access[i]);
	}

  return NULL;
}

extern int
main(int argc, char *argv[])
{
  int i, nthread = 4;
  struct timeval begin, end;
	pthread_t *thread;
	
	if (argc == 2) nthread = atoi(argv[1]);
	thread = (pthread_t *)calloc(nthread, sizeof(pthread_t));
	if (!thread) ERR;
	
	gettimeofday(&begin, NULL);
  for (i = 0; i < nthread; i++) {
    int ret = pthread_create(&thread[i], NULL, worker, NULL);
		if (ret < 0) ERR;
	}

  for (i = 0; i < nthread; i++) {
		int ret = pthread_join(thread[i], NULL);
		if (ret < 0) ERR;
	}
  gettimeofday(&end, NULL);
  print_result(begin, end, nthread);
	free(thread);
	
  return 0;
}
