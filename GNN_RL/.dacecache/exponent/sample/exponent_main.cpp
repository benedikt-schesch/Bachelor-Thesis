#include <stdlib.h>
#include "exponent.h"

int main(int argc, char** argv) {
  dace::complex64 * __restrict__ A = (dace::complex64*) calloc(576, sizeof(dace::complex64));
  dace::complex64 * __restrict__ B = (dace::complex64*) calloc(576, sizeof(dace::complex64));

  __dace_init_exponent(A, B);
  __program_exponent(A, B);
  __dace_exit_exponent(A, B);

  free(A);
  free(B);
  return 0;
}
