#include <stdio.h>

#include <mpp/shmem.h>

long L = 0;

int
main(int argc, char **argv)
{
  int me;
  int slp;

  start_pes(0);
  me = _my_pe();
  slp = me + 1;

  shmem_barrier_all();

  if (me == 1) sleep(3);

  shmem_set_lock(&L);

  printf("%d: sleeping %d seconds...\n", me, slp);
  sleep(slp);
  printf("%d: sleeping...done\n", me);

  shmem_clear_lock(&L);

  shmem_barrier_all();

  return 0;
}
