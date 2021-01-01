#include <stdlib.h>
#include "multiply.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ X = (double*) calloc(N, sizeof(double));
  double * __restrict__ Y = (double*) calloc(N, sizeof(double));
  double * __restrict__ Z = (double*) calloc(N, sizeof(double));

  __dace_init_multiply(X, Y, Z, N);
  __program_multiply(X, Y, Z, N);
  __dace_exit_multiply(X, Y, Z, N);

  free(X);
  free(Y);
  free(Z);
  return 0;
}
