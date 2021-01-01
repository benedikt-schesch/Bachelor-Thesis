#include <stdlib.h>
#include "multiple_tasklets.h"

int main(int argc, char** argv) {
  int N = 42;
  int * __restrict__ A = (int*) calloc(N, sizeof(int));
  int * __restrict__ B = (int*) calloc(N, sizeof(int));

  __dace_init_multiple_tasklets(A, B, N);
  __program_multiple_tasklets(A, B, N);
  __dace_exit_multiple_tasklets(A, B, N);

  free(A);
  free(B);
  return 0;
}
