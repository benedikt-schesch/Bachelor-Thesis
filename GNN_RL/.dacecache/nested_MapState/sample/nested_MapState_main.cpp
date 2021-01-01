#include <stdlib.h>
#include "nested_MapState.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(((1024 * (255 / 8)) + 1024), sizeof(float));
  float * __restrict__ B = (float*) calloc(((1024 * (255 / 8)) + 1024), sizeof(float));
  float * __restrict__ C = (float*) calloc(16384, sizeof(float));

  __dace_init_nested_MapState(A, B, C);
  __program_nested_MapState(A, B, C);
  __dace_exit_nested_MapState(A, B, C);

  free(A);
  free(B);
  free(C);
  return 0;
}
