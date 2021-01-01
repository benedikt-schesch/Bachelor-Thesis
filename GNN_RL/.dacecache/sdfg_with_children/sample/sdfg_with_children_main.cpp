#include <stdlib.h>
#include "sdfg_with_children.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc((N * N), sizeof(float));
  float * __restrict__ B = (float*) calloc((N * N), sizeof(float));

  __dace_init_sdfg_with_children(A, B, N);
  __program_sdfg_with_children(A, B, N);
  __dace_exit_sdfg_with_children(A, B, N);

  free(A);
  free(B);
  return 0;
}
