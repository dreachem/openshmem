/* (c) 2011 University of Houston.  All rights reserved. */


/*
 * rotate put an array to right neighbor
 */

#include <stdio.h>
#include <time.h>

#include <mpp/shmem.h>

#define N 7

int
main(int argc, char **argv)
{
  int i;
  int nextpe;
  int me, npes;
  long src[N];
  long *dest;

  start_pes(0);
  me = _my_pe();
  npes = _num_pes();

  for (i = 0; i < N; i += 1) {
    src[i] = (long)me;
  }

  dest = (long *)shmalloc( N * sizeof(*dest) );

  nextpe = (me + 1) % npes;

  shmem_long_put(dest, src, N, nextpe);

  shmem_barrier_all();

  for (i = 0; i < N; i += 1) {
    printf("%d @ %s: dest[%d] = %ld\n", me, shmem_nodename(), i, dest[i]);
  }

  shfree(dest);

  return 0;
}
