#include <stdlib.h>
#include "test_sum.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(150, sizeof(double));
  double * __restrict__ __return = (double*) calloc(1, sizeof(double));

  __dace_init_test_sum(A, __return);
  __program_test_sum(A, __return);
  __dace_exit_test_sum(A, __return);

  free(A);
  free(__return);
  return 0;
}
