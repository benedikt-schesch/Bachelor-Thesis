#include <stdlib.h>
#include "dot_product_pure_float.h"

int main(int argc, char** argv) {
  int n = 42;
  float * __restrict__ result = (float*) calloc(1, sizeof(float));
  float * __restrict__ x = (float*) calloc(n, sizeof(float));
  float * __restrict__ y = (float*) calloc(n, sizeof(float));

  __dace_init_dot_product_pure_float(result, x, y, n);
  __program_dot_product_pure_float(result, x, y, n);
  __dace_exit_dot_product_pure_float(result, x, y, n);

  free(result);
  free(x);
  free(y);
  return 0;
}
