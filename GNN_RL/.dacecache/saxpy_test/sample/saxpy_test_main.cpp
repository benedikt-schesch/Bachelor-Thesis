#include <stdlib.h>
#include "saxpy_test.h"

int main(int argc, char** argv) {
  int n = 42;
  float * __restrict__ x1 = (float*) calloc(n, sizeof(float));
  float * __restrict__ y1 = (float*) calloc(n, sizeof(float));
  float * __restrict__ z1 = (float*) calloc(n, sizeof(float));

  __dace_init_saxpy_test(x1, y1, z1, n);
  __program_saxpy_test(x1, y1, z1, n);
  __dace_exit_saxpy_test(x1, y1, z1, n);

  free(x1);
  free(y1);
  free(z1);
  return 0;
}
