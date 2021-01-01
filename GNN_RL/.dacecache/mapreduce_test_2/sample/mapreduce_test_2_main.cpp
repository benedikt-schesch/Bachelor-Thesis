#include <stdlib.h>
#include "mapreduce_test_2.h"

int main(int argc, char** argv) {
  int K = 42;
  int M = 42;
  int N = 42;
  double * __restrict__ A = (double*) calloc((M * N), sizeof(double));
  double * __restrict__ B = (double*) calloc((K * N), sizeof(double));
  double * __restrict__ C = (double*) calloc((K * M), sizeof(double));

  __dace_init_mapreduce_test_2(A, B, C, K, M, N);
  __program_mapreduce_test_2(A, B, C, K, M, N);
  __dace_exit_mapreduce_test_2(A, B, C, K, M, N);

  free(A);
  free(B);
  free(C);
  return 0;
}
