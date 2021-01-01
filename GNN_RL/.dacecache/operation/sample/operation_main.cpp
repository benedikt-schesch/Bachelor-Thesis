#include <stdlib.h>
#include "operation.h"

int main(int argc, char** argv) {
  int M = 42;
  int N = 42;
  double * __restrict__ A = (double*) calloc((M * M), sizeof(double));
  double * __restrict__ B = (double*) calloc((M * M), sizeof(double));
  double * __restrict__ C = (double*) calloc((M * N), sizeof(double));
  double * __restrict__ D = (double*) calloc((M * N), sizeof(double));

  __dace_init_operation(A, B, C, D, M, N);
  __program_operation(A, B, C, D, M, N);
  __dace_exit_operation(A, B, C, D, M, N);

  free(A);
  free(B);
  free(C);
  free(D);
  return 0;
}
