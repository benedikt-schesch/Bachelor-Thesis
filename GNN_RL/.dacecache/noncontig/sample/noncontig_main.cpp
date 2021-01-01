#include <stdlib.h>
#include "noncontig.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(24, sizeof(float));
  float * __restrict__ B = (float*) calloc(24, sizeof(float));

  __dace_init_noncontig(A, B);
  __program_noncontig(A, B);
  __dace_exit_noncontig(A, B);

  free(A);
  free(B);
  return 0;
}
