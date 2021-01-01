#include <stdlib.h>
#include "exponent_m.h"

int main(int argc, char** argv) {
  dace::complex64 * __restrict__ A = (dace::complex64*) calloc(576, sizeof(dace::complex64));
  dace::complex64 * __restrict__ B = (dace::complex64*) calloc(576, sizeof(dace::complex64));

  __dace_init_exponent_m(A, B);
  __program_exponent_m(A, B);
  __dace_exit_exponent_m(A, B);

  free(A);
  free(B);
  return 0;
}
