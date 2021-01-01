#include <stdlib.h>
#include "slicetest.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ A = (double*) calloc((N * (N - 1)), sizeof(double));
  double * __restrict__ B = (double*) calloc((N * (N - 1)), sizeof(double));
  double * __restrict__ C = (double*) calloc(((N - 1) * (N - 1)), sizeof(double));

  __dace_init_slicetest(A, B, C, N);
  __program_slicetest(A, B, C, N);
  __dace_exit_slicetest(A, B, C, N);

  free(A);
  free(B);
  free(C);
  return 0;
}
