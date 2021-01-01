#include <stdlib.h>
#include "transpose_tiled.h"

int main(int argc, char** argv) {
  int H = 42;
  int TH = 42;
  int TW = 42;
  int W = 42;
  float * __restrict__ A = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ B = (float*) calloc((H * W), sizeof(float));

  __dace_init_transpose_tiled(A, B, H, TH, TW, W);
  __program_transpose_tiled(A, B, H, TH, TW, W);
  __dace_exit_transpose_tiled(A, B, H, TH, TW, W);

  free(A);
  free(B);
  return 0;
}
