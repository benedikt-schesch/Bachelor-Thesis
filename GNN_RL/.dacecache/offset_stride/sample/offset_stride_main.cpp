#include <stdlib.h>
#include "offset_stride.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc(36, sizeof(float));
  float * __restrict__ B = (float*) calloc(6, sizeof(float));

  __dace_init_offset_stride(A, B, N);
  __program_offset_stride(A, B, N);
  __dace_exit_offset_stride(A, B, N);

  free(A);
  free(B);
  return 0;
}
