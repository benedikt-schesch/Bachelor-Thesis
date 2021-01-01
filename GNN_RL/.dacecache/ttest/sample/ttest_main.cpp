#include <stdlib.h>
#include "ttest.h"

int main(int argc, char** argv) {
  int K = 42;
  int M = 42;
  int N = 42;
  float * __restrict__ A = (float*) calloc(((K * M) * N), sizeof(float));
  float * __restrict__ B = (float*) calloc(((K * M) * N), sizeof(float));

  __dace_init_ttest(A, B, K, M, N);
  __program_ttest(A, B, K, M, N);
  __dace_exit_ttest(A, B, K, M, N);

  free(A);
  free(B);
  return 0;
}
