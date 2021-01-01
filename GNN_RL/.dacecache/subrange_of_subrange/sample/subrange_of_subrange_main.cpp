#include <stdlib.h>
#include "subrange_of_subrange.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(120, sizeof(float));
  float * __restrict__ B = (float*) calloc(4, sizeof(float));

  __dace_init_subrange_of_subrange(A, B);
  __program_subrange_of_subrange(A, B);
  __dace_exit_subrange_of_subrange(A, B);

  free(A);
  free(B);
  return 0;
}
