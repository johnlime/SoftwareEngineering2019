#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/time.h>
#include <string.h>
#include "debug.h"

#define SZ_PAGE 4096
#define NB_BUFR (SZ_PAGE * 2 / sizeof(TUPLE))
#define NB_BUFS (SZ_PAGE * 16 / sizeof(TUPLE))

typedef struct _TUPLE {
  int key;
  int val;
} TUPLE;

typedef struct _RESULT {
  int rkey;
  int rval;
  int skey;
  int sval;
} RESULT;

typedef struct _HASHOBJ {
  TUPLE tuple;
  struct _HASHOBJ *nxt;
} HASHOBJ;

typedef struct _BUCKET {
  HASHOBJ head;
  HASHOBJ *tail;
} BUCKET;

#define NB_BUCKET NB_BUFR


void
printDiff(struct timeval begin, struct timeval end)
{
  long diff;

  diff = (end.tv_sec - begin.tv_sec) * 1000 * 1000 + (end.tv_usec - begin.tv_usec);
  printf("Diff: %ld us (%ld ms)\n", diff, diff/1000);
}

long
calcDiff(struct timeval begin, struct timeval end)
{
  long diff;
  diff = (end.tv_sec - begin.tv_sec) * 1000 * 1000 + (end.tv_usec - begin.tv_usec);
  return diff;
}

int 
main(void)
{
  int rfd;
  int sfd;
  int nr;
  int ns;
  TUPLE bufR[NB_BUFR];
  TUPLE bufS[NB_BUFS];
  RESULT result;
  int resultVal = 0;
  struct timeval begin, end;
  BUCKET bucket[NB_BUCKET];

  gettimeofday(&begin, NULL);
  rfd = open("R", O_RDONLY); if (rfd == -1) ERR;
  sfd = open("S", O_RDONLY); if (sfd == -1) ERR;
  bzero(bucket, sizeof(BUCKET) * NB_BUCKET);

  int cnt = 0;
  long iodiff = 0;
  long joindiff = 0;

  while (true) {
    nr = read(rfd, bufR, NB_BUFR * sizeof(TUPLE));
    if (nr == -1) ERR; else if (nr == 0) break;

    /* Write your code [Cleanup hash bucket]*/

    /* Write your code [Construct Hash] */

    if ((lseek(sfd, 0, SEEK_SET)) == -1) ERR;    
    while (true) {
      struct timeval bio, eio;
      struct timeval bjoin, ejoin;

      gettimeofday(&bio, NULL);
      ns = read(sfd, bufS, NB_BUFS * sizeof(TUPLE));
      if (ns == -1) ERR; else if (ns == 0) break;
      gettimeofday(&eio, NULL);
      iodiff += calcDiff(bio, eio);

      cnt++;

      gettimeofday(&bjoin, NULL);
      /* Write your code [Exec Join] */
      gettimeofday(&ejoin, NULL);
      joindiff += calcDiff(bjoin, ejoin);
    }
  }
  gettimeofday(&end, NULL);

  printDiff(begin, end);
  printf("Result: %d\n", resultVal);
  //printf("iodiff: %ld\n", iodiff);
  //printf("joindiff: %ld\n", joindiff);

  return 0;
}
