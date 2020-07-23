#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#ifdef USE_JEMALLOC
#include <jemalloc/jemalloc.h>
#endif

#define MSECOND 1000000

int main(void)
{
  int i = 0;
  size_t j = 0;
  char pad = 0;
  char* ptr = NULL;
  size_t size = 128;
  float timeuse = 0;
  struct timeval tpstart;
  struct timeval tpend;
  int loops = 1e8;
  int value = 1;

  const size_t batch_size = 1e6;
  char** to_free = malloc(batch_size * sizeof(char*));
  for (j = 0; j < batch_size; ++j) {
    to_free[j] = NULL;
  }

  srand((int)time(0));

  gettimeofday(&tpstart, NULL);
  for (i = 0; i < loops; i++) {
    size = rand() & 0xff;
    ptr = malloc(size);
    // to some work and write new area
    value = value * (value + 1);
    *((int*)ptr) = value;
    // free in batch
    if (i > 0 && i % batch_size == 0) {
      for (j = 0; j < batch_size; ++j) {
        free(to_free[j]);
        to_free[j] = NULL;
      }
    }
    to_free[i % batch_size] = ptr;
  }
  gettimeofday(&tpend, NULL);

#ifdef USE_JEMALLOC
  //malloc_stats_print(NULL, NULL, NULL);
#endif

  timeuse=MSECOND*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec;
  timeuse/=MSECOND;
  printf("Used Time [%f] with [%d] loops\n", timeuse, loops);

  return 0;
}
