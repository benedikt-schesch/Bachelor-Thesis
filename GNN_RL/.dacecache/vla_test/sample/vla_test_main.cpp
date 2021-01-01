#include <stdlib.h>
#include "vla_test.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc(N, sizeof(float));
  float * __restrict__ B = (float*) calloc(N, sizeof(float));

  __dace_init_vla_test(A, B, N);
  __program_vla_test(A, B, N);
  __dace_exit_vla_test(A, B, N);

  free(A);
  free(B);
  return 0;
}
