#include <stdlib.h>
#include "test_min_int64.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(150, sizeof(long long));
  long long * __restrict__ __return = (long long*) calloc(30, sizeof(long long));

  __dace_init_test_min_int64(A, __return);
  __program_test_min_int64(A, __return);
  __dace_exit_test_min_int64(A, __return);

  free(A);
  free(__return);
  return 0;
}
