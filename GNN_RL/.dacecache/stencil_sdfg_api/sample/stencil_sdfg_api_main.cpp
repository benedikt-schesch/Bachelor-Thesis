#include <stdlib.h>
#include "stencil_sdfg_api.h"

int main(int argc, char** argv) {
  int H = 42;
  int MAXITER = 42;
  int W = 42;
  float * __restrict__ A = (float*) calloc((H * W), sizeof(float));

  __dace_init_stencil_sdfg_api(A, H, MAXITER, W);
  __program_stencil_sdfg_api(A, H, MAXITER, W);
  __dace_exit_stencil_sdfg_api(A, H, MAXITER, W);

  free(A);
  return 0;
}
