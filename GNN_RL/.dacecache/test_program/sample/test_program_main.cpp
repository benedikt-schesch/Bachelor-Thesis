#include <stdlib.h>
#include "test_program.h"

int main(int argc, char** argv) {
  int M = 42;
  int N = 42;
  int O = 42;
  double * __restrict__ A = (double*) calloc(N, sizeof(double));
  double * __restrict__ B = (double*) calloc(M, sizeof(double));
  double * __restrict__ C = (double*) calloc(O, sizeof(double));
  double * __restrict__ out1 = (double*) calloc((M * N), sizeof(double));
  double * __restrict__ out2 = (double*) calloc(1, sizeof(double));
  double * __restrict__ out3 = (double*) calloc(((M * N) * O), sizeof(double));

  __dace_init_test_program(A, B, C, out1, out2, out3, M, N, O);
  __program_test_program(A, B, C, out1, out2, out3, M, N, O);
  __dace_exit_test_program(A, B, C, out1, out2, out3, M, N, O);

  free(A);
  free(B);
  free(C);
  free(out1);
  free(out2);
  free(out3);
  return 0;
}
