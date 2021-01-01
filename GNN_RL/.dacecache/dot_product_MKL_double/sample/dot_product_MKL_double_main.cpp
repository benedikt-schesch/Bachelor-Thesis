#include <stdlib.h>
#include "dot_product_MKL_double.h"

int main(int argc, char** argv) {
  int n = 42;
  double * __restrict__ result = (double*) calloc(1, sizeof(double));
  double * __restrict__ x = (double*) calloc(n, sizeof(double));
  double * __restrict__ y = (double*) calloc(n, sizeof(double));

  __dace_init_dot_product_MKL_double(result, x, y, n);
  __program_dot_product_MKL_double(result, x, y, n);
  __dace_exit_dot_product_MKL_double(result, x, y, n);

  free(result);
  free(x);
  free(y);
  return 0;
}
