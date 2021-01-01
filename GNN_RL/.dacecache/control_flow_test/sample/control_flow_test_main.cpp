#include <stdlib.h>
#include "control_flow_test.h"

int main(int argc, char** argv) {
  int H = 42;
  int W = 42;
  float * __restrict__ A = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ B = (float*) calloc((H * W), sizeof(float));
  float * __restrict__ tol = (float*) calloc(1, sizeof(float));

  __dace_init_control_flow_test(A, B, tol, H, W);
  __program_control_flow_test(A, B, tol, H, W);
  __dace_exit_control_flow_test(A, B, tol, H, W);

  free(A);
  free(B);
  free(tol);
  return 0;
}
