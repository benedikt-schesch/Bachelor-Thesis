#include <stdlib.h>
#include "subrange3.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(24, sizeof(float));
  float * __restrict__ B = (float*) calloc(12, sizeof(float));

  __dace_init_subrange3(A, B);
  __program_subrange3(A, B);
  __dace_exit_subrange3(A, B);

  free(A);
  free(B);
  return 0;
}
