#include <stdlib.h>
#include "dTGL_test.h"

int main(int argc, char** argv) {
  int BS = 42;
  int N = 42;
  dace::complex128 * __restrict__ HD = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ HE = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ dTGL = (dace::complex128*) calloc(N, sizeof(dace::complex128));

  __dace_init_dTGL_test(HD, HE, dTGL, BS, N);
  __program_dTGL_test(HD, HE, dTGL, BS, N);
  __dace_exit_dTGL_test(HD, HE, dTGL, BS, N);

  free(HD);
  free(HE);
  free(dTGL);
  return 0;
}
