#include <stdlib.h>
#include "multiple_fusions.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(200, sizeof(float));
  float * __restrict__ B = (float*) calloc(200, sizeof(float));
  float * __restrict__ C = (float*) calloc(200, sizeof(float));
  float * __restrict__ out = (float*) calloc(1, sizeof(float));

  __dace_init_multiple_fusions(A, B, C, out);
  __program_multiple_fusions(A, B, C, out);
  __dace_exit_multiple_fusions(A, B, C, out);

  free(A);
  free(B);
  free(C);
  free(out);
  return 0;
}
