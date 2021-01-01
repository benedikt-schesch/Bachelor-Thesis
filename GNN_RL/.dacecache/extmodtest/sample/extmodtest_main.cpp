#include <stdlib.h>
#include "extmodtest.h"

int main(int argc, char** argv) {
  int H = 42;
  int W = 42;
  float * __restrict__ A = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ result = (float*) calloc(1, sizeof(float));

  __dace_init_extmodtest(A, result, H, W);
  __program_extmodtest(A, result, H, W);
  __dace_exit_extmodtest(A, result, H, W);

  free(A);
  free(result);
  return 0;
}
