#include <stdlib.h>
#include "outer_sdfg.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc((N * N), sizeof(float));
  float * __restrict__ B = (float*) calloc((N * N), sizeof(float));

  __dace_init_outer_sdfg(A, B, N);
  __program_outer_sdfg(A, B, N);
  __dace_exit_outer_sdfg(A, B, N);

  free(A);
  free(B);
  return 0;
}
