#include <stdlib.h>
#include "test_return_both.h"

int main(int argc, char** argv) {
  double * __restrict__ IN = (double*) calloc(150, sizeof(double));
  int * __restrict__ __tmp1 = (int*) calloc(30, sizeof(int));
  double * __restrict__ __tmp2 = (double*) calloc(30, sizeof(double));

  __dace_init_test_return_both(IN, __tmp1, __tmp2);
  __program_test_return_both(IN, __tmp1, __tmp2);
  __dace_exit_test_return_both(IN, __tmp1, __tmp2);

  free(IN);
  free(__tmp1);
  free(__tmp2);
  return 0;
}
