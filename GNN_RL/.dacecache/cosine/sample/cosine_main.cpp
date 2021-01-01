#include <stdlib.h>
#include "cosine.h"

int main(int argc, char** argv) {
  dace::complex64 * __restrict__ A = (dace::complex64*) calloc(576, sizeof(dace::complex64));
  dace::complex64 * __restrict__ B = (dace::complex64*) calloc(576, sizeof(dace::complex64));

  __dace_init_cosine(A, B);
  __program_cosine(A, B);
  __dace_exit_cosine(A, B);

  free(A);
  free(B);
  return 0;
}
