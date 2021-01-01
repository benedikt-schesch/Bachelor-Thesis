#include <stdlib.h>
#include "confres_test.h"

int main(int argc, char** argv) {
  int H = 42;
  int W = 42;
  float * __restrict__ A = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ B = (float*) calloc(((H * H) * W), sizeof(float));
  float * __restrict__ red1 = (float*) calloc(3, sizeof(float));
  float * __restrict__ red2 = (float*) calloc(1, sizeof(float));

  __dace_init_confres_test(A, B, red1, red2, H, W);
  __program_confres_test(A, B, red1, red2, H, W);
  __dace_exit_confres_test(A, B, red1, red2, H, W);

  free(A);
  free(B);
  free(red1);
  free(red2);
  return 0;
}
