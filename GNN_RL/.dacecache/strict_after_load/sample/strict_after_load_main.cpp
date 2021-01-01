#include <stdlib.h>
#include "strict_after_load.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(200, sizeof(float));
  float * __restrict__ B = (float*) calloc(200, sizeof(float));

  __dace_init_strict_after_load(A, B);
  __program_strict_after_load(A, B);
  __dace_exit_strict_after_load(A, B);

  free(A);
  free(B);
  return 0;
}
