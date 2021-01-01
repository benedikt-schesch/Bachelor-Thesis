#include <stdlib.h>
#include "real_part.h"

int main(int argc, char** argv) {
  dace::complex64 * __restrict__ A = (dace::complex64*) calloc(576, sizeof(dace::complex64));
  float * __restrict__ B = (float*) calloc(576, sizeof(float));

  __dace_init_real_part(A, B);
  __program_real_part(A, B);
  __dace_exit_real_part(A, B);

  free(A);
  free(B);
  return 0;
}
