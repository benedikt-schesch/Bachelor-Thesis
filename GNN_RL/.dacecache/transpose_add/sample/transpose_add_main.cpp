#include <stdlib.h>
#include "transpose_add.h"

int main(int argc, char** argv) {
  int K = 42;
  int M = 42;
  float * __restrict__ A = (float*) calloc((K * M), sizeof(float));
  float * __restrict__ B = (float*) calloc((K * M), sizeof(float));

  __dace_init_transpose_add(A, B, K, M);
  __program_transpose_add(A, B, K, M);
  __dace_exit_transpose_add(A, B, K, M);

  free(A);
  free(B);
  return 0;
}
