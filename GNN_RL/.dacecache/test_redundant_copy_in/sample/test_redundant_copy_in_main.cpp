#include <stdlib.h>
#include "test_redundant_copy_in.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(9, sizeof(float));
  float * __restrict__ D = (float*) calloc(9, sizeof(float));

  __dace_init_test_redundant_copy_in(A, D);
  __program_test_redundant_copy_in(A, D);
  __dace_exit_test_redundant_copy_in(A, D);

  free(A);
  free(D);
  return 0;
}