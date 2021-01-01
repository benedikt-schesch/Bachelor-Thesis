#include <stdlib.h>
#include "myprogram.h"

int main(int argc, char** argv) {
  int H = 42;
  int W = 42;
  float * __restrict__ A = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ B = (float*) calloc((H * W), sizeof(float));

  __dace_init_myprogram(A, B, H, W);
  __program_myprogram(A, B, H, W);
  __dace_exit_myprogram(A, B, H, W);

  free(A);
  free(B);
  return 0;
}
