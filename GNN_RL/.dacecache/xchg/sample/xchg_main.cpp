#include <stdlib.h>
#include "xchg.h"

int main(int argc, char** argv) {
  int * __restrict__ locked = (int*) calloc(1, sizeof(int));
  int * __restrict__ output = (int*) calloc(20, sizeof(int));

  __dace_init_xchg(locked, output);
  __program_xchg(locked, output);
  __dace_exit_xchg(locked, output);

  free(locked);
  free(output);
  return 0;
}
