#include <stdlib.h>
#include "fusion.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(200, sizeof(float));
  float * __restrict__ B = (float*) calloc(200, sizeof(float));
  float * __restrict__ out = (float*) calloc(1, sizeof(float));

  __dace_init_fusion(A, B, out);
  __program_fusion(A, B, out);
  __dace_exit_fusion(A, B, out);

  free(A);
  free(B);
  free(out);
  return 0;
}
