#include <stdlib.h>
#include "test_min_1.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(150, sizeof(double));
  double * __restrict__ __return = (double*) calloc(30, sizeof(double));

  __dace_init_test_min_1(A, __return);
  __program_test_min_1(A, __return);
  __dace_exit_test_min_1(A, __return);

  free(A);
  free(__return);
  return 0;
}
