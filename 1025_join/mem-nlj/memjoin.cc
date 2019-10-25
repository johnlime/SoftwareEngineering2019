#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include "debug.h"

#define NB_BUFR (10)
#define NB_BUFS (10)

typedef struct _TUPLE {
  int key;
  int val;
} TUPLE;

void
printDiff(struct timeval begin, struct timeval end)
{
  long diff;

  diff = (end.tv_sec - begin.tv_sec) * 1000 * 1000 + (end.tv_usec - begin.tv_usec);
  printf("Diff: %ld us (%ld ms)\n", diff, diff/1000);
}

int 
main(void)
{
  TUPLE bufR[NB_BUFR];
  TUPLE bufS[NB_BUFS];

  /* init */
	for (int i = 0; i < NB_BUFR; i++) {
		bufS[i].key = bufR[i].key = i;
		bufS[i].val = bufR[i].val = i * 10;
	}

  /* join */
	for (int i = 0; i < NB_BUFR; i++) {
		for (int j = 0; j < NB_BUFS; j++) {
			if (bufR[i].key == bufS[j].key) {
				printf("%2d:%2d:%2d:%2d\n", bufR[i].key, bufR[i].val, bufS[i].key,bufS[i].val);
			}
    }
  }

  return 0;
}
