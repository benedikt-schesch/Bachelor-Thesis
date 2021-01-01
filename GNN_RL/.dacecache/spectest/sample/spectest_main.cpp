#include <stdlib.h>
#include "spectest.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc((M * N), sizeof(float));
  float * __restrict__ B = (float*) calloc((M * N), sizeof(float));

  __dace_init_spectest(A, B);
  __program_spectest(A, B);
  __dace_exit_spectest(A, B);

  free(A);
  free(B);
  return 0;
}
