#include <stdlib.h>
#include "indirection.h"

int main(int argc, char** argv) {
  int M = 42;
  int N = 42;
  double * __restrict__ A = (double*) calloc(M, sizeof(double));
  int * __restrict__ x = (int*) calloc(N, sizeof(int));

  __dace_init_indirection(A, x, M, N);
  __program_indirection(A, x, M, N);
  __dace_exit_indirection(A, x, M, N);

  free(A);
  free(x);
  return 0;
}
