#include <stdlib.h>
#include "test_argmax_1.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(150, sizeof(double));
  int * __restrict__ __return = (int*) calloc(30, sizeof(int));

  __dace_init_test_argmax_1(A, __return);
  __program_test_argmax_1(A, __return);
  __dace_exit_test_argmax_1(A, __return);

  free(A);
  free(__return);
  return 0;
}
