#include <stdlib.h>
#include "nested_reduction.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(40, sizeof(float));
  float * __restrict__ B = (float*) calloc(20, sizeof(float));

  __dace_init_nested_reduction(A, B);
  __program_nested_reduction(A, B);
  __dace_exit_nested_reduction(A, B);

  free(A);
  free(B);
  return 0;
}
