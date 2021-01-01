#include <stdlib.h>
#include "mmmtest.h"

int main(int argc, char** argv) {
  int B = 42;
  int K = 42;
  int M = 42;
  int N = 42;
  double * __restrict__ __return = (double*) calloc(((B * M) * N), sizeof(double));
  double * __restrict__ a = (double*) calloc((K * M), sizeof(double));
  double * __restrict__ b = (double*) calloc(((B * K) * N), sizeof(double));

  __dace_init_mmmtest(__return, a, b, B, K, M, N);
  __program_mmmtest(__return, a, b, B, K, M, N);
  __dace_exit_mmmtest(__return, a, b, B, K, M, N);

  free(__return);
  free(a);
  free(b);
  return 0;
}
