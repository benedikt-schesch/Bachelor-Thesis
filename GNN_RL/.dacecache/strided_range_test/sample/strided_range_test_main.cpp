#include <stdlib.h>
#include "strided_range_test.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(128, sizeof(float));
  float * __restrict__ B = (float*) calloc(16, sizeof(float));

  __dace_init_strided_range_test(A, B);
  __program_strided_range_test(A, B);
  __dace_exit_strided_range_test(A, B);

  free(A);
  free(B);
  return 0;
}
