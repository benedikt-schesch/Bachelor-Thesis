#include <stdlib.h>
#include "test_program2.h"

int main(int argc, char** argv) {
  int M = 42;
  int N = 42;
  double * __restrict__ A = (double*) calloc((M * N), sizeof(double));
  double * __restrict__ B = (double*) calloc((M * N), sizeof(double));
  double * __restrict__ C = (double*) calloc(N, sizeof(double));

  __dace_init_test_program2(A, B, C, M, N);
  __program_test_program2(A, B, C, M, N);
  __dace_exit_test_program2(A, B, C, M, N);

  free(A);
  free(B);
  free(C);
  return 0;
}
