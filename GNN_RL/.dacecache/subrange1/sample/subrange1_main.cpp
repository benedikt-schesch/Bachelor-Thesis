#include <stdlib.h>
#include "subrange1.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(24, sizeof(float));
  float * __restrict__ B = (float*) calloc(12, sizeof(float));

  __dace_init_subrange1(A, B);
  __program_subrange1(A, B);
  __dace_exit_subrange1(A, B);

  free(A);
  free(B);
  return 0;
}
