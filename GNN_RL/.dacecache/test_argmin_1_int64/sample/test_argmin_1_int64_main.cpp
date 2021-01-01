#include <stdlib.h>
#include "test_argmin_1_int64.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(150, sizeof(long long));
  int * __restrict__ __return = (int*) calloc(30, sizeof(int));

  __dace_init_test_argmin_1_int64(A, __return);
  __program_test_argmin_1_int64(A, __return);
  __dace_exit_test_argmin_1_int64(A, __return);

  free(A);
  free(__return);
  return 0;
}
