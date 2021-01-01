#include <stdlib.h>
#include "seq_cond.h"

int main(int argc, char** argv) {
  int BS = 42;
  int N = 42;
  dace::complex128 * __restrict__ HD = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ HE = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ HF = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaRSD = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaRSE = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaRSF = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));

  __dace_init_seq_cond(HD, HE, HF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);
  __program_seq_cond(HD, HE, HF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);
  __dace_exit_seq_cond(HD, HE, HF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);

  free(HD);
  free(HE);
  free(HF);
  free(sigmaRSD);
  free(sigmaRSE);
  free(sigmaRSF);
  return 0;
}
