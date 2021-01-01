#include <stdlib.h>
#include "myvmin.h"

int main(int argc, char** argv) {
  int N = 42;
  float * __restrict__ A = (float*) calloc(N, sizeof(float));
  float * __restrict__ B = (float*) calloc(N, sizeof(float));
  float * __restrict__ C = (float*) calloc(N, sizeof(float));

  __dace_init_myvmin(A, B, C, N);
  __program_myvmin(A, B, C, N);
  __dace_exit_myvmin(A, B, C, N);

  free(A);
  free(B);
  free(C);
  return 0;
}
