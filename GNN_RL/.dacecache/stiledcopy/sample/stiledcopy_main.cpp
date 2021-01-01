#include <stdlib.h>
#include "stiledcopy.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(128, sizeof(float));
  float * __restrict__ B = (float*) calloc(4, sizeof(float));
  float * __restrict__ C = (float*) calloc(128, sizeof(float));
  float * __restrict__ D = (float*) calloc(16384, sizeof(float));
  float * __restrict__ E = (float*) calloc(64, sizeof(float));
  float * __restrict__ F = (float*) calloc(16384, sizeof(float));

  __dace_init_stiledcopy(A, B, C, D, E, F);
  __program_stiledcopy(A, B, C, D, E, F);
  __dace_exit_stiledcopy(A, B, C, D, E, F);

  free(A);
  free(B);
  free(C);
  free(D);
  free(E);
  free(F);
  return 0;
}
