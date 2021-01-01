#include <stdlib.h>
#include "stencil3x3.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc((N * N), sizeof(float));
  float * __restrict__ B = (float*) calloc((N * N), sizeof(float));

  __dace_init_stencil3x3(A, B, N);
  __program_stencil3x3(A, B, N);
  __dace_exit_stencil3x3(A, B, N);

  free(A);
  free(B);
  return 0;
}
