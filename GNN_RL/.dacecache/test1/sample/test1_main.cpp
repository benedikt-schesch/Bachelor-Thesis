#include <stdlib.h>
#include "test1.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ A = (double*) calloc(N, sizeof(double));
  double * __restrict__ B = (double*) calloc(N, sizeof(double));

  __dace_init_test1(A, B, N);
  __program_test1(A, B, N);
  __dace_exit_test1(A, B, N);

  free(A);
  free(B);
  return 0;
}
