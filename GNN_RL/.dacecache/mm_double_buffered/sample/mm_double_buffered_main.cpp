#include <stdlib.h>
#include "mm_double_buffered.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(65536, sizeof(float));
  float * __restrict__ B = (float*) calloc(65536, sizeof(float));
  float * __restrict__ C = (float*) calloc(65536, sizeof(float));

  __dace_init_mm_double_buffered(A, B, C);
  __program_mm_double_buffered(A, B, C);
  __dace_exit_mm_double_buffered(A, B, C);

  free(A);
  free(B);
  free(C);
  return 0;
}
