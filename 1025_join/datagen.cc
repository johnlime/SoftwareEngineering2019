#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FILE "FILE"
#define MAX (1000*1000)
typedef struct _DATA {
  int key;
  int value;
} DATA;

int
main(void)
{
  int fd;
  DATA d;
  fd = open(FILE, O_WRONLY|O_CREAT, 0644);

  for (int i = 0; i < MAX; i++) {
    write(fd, &d, sizeof(DATA));
  }

  close(fd);

  return 0;
}
