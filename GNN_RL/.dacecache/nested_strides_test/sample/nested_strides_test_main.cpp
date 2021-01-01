#include <stdlib.h>
#include "nested_strides_test.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(24, sizeof(float));
  float * __restrict__ B = (float*) calloc(12, sizeof(float));

  __dace_init_nested_strides_test(A, B);
  __program_nested_strides_test(A, B);
  __dace_exit_nested_strides_test(A, B);

  free(A);
  free(B);
  return 0;
}
