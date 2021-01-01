#include <stdlib.h>
#include "dup.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(1, sizeof(float));
  float * __restrict__ B = (float*) calloc(1, sizeof(float));
  float * __restrict__ C = (float*) calloc(1, sizeof(float));
  float * __restrict__ D = (float*) calloc(1, sizeof(float));
  float * __restrict__ E = (float*) calloc(1, sizeof(float));
  float * __restrict__ F = (float*) calloc(1, sizeof(float));

  __dace_init_dup(A, B, C, D, E, F);
  __program_dup(A, B, C, D, E, F);
  __dace_exit_dup(A, B, C, D, E, F);

  free(A);
  free(B);
  free(C);
  free(D);
  free(E);
  free(F);
  return 0;
}
