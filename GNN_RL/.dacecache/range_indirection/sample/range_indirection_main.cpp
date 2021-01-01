#include <stdlib.h>
#include "range_indirection.h"

int main(int argc, char** argv) {
  int M = 42;
  int N = 42;
  double * __restrict__ A = (double*) calloc((M * N), sizeof(double));
  int * __restrict__ x = (int*) calloc(M, sizeof(int));

  __dace_init_range_indirection(A, x, M, N);
  __program_range_indirection(A, x, M, N);
  __dace_exit_range_indirection(A, x, M, N);

  free(A);
  free(x);
  return 0;
}
