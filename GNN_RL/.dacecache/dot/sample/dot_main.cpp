#include <stdlib.h>
#include "dot.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc(64, sizeof(float));
  float * __restrict__ B = (float*) calloc(64, sizeof(float));
  double * __restrict__ out = (double*) calloc(1, sizeof(double));

  __dace_init_dot(A, B, out, N);
  __program_dot(A, B, out, N);
  __dace_exit_dot(A, B, out, N);

  free(A);
  free(B);
  free(out);
  return 0;
}
