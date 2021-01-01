#include <stdlib.h>
#include "arange.h"

int main(int argc, char** argv) {
  int N = 42;
  int * __restrict__ __return = (int*) calloc(N, sizeof(int));

  __dace_init_arange(__return, N);
  __program_arange(__return, N);
  __dace_exit_arange(__return, N);

  free(__return);
  return 0;
}
