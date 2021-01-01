#include <stdlib.h>
#include "slowmm.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ A = (double*) calloc((N * N), sizeof(double));
  double * __restrict__ B = (double*) calloc((N * N), sizeof(double));
  double * __restrict__ C = (double*) calloc((N * N), sizeof(double));

  __dace_init_slowmm(A, B, C, N);
  __program_slowmm(A, B, C, N);
  __dace_exit_slowmm(A, B, C, N);

  free(A);
  free(B);
  free(C);
  return 0;
}
