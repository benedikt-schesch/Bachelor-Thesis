#include <stdlib.h>
#include "rgf_dense.h"

int main(int argc, char** argv) {
  int BS = 42;
  int N = 42;
  dace::complex128 * __restrict__ GG = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ GL = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ HD = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ HE = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ HF = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ dTGL = (dace::complex128*) calloc(N, sizeof(dace::complex128));
  double * __restrict__ fl = (double*) calloc(1, sizeof(double));
  double * __restrict__ fr = (double*) calloc(1, sizeof(double));
  dace::complex128 * __restrict__ gammaleft = (dace::complex128*) calloc((BS * BS), sizeof(dace::complex128));
  dace::complex128 * __restrict__ gammaright = (dace::complex128*) calloc((BS * BS), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigRl = (dace::complex128*) calloc((BS * BS), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigRr = (dace::complex128*) calloc((BS * BS), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaGSD = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaGSE = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaGSF = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaLSD = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaLSE = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaLSF = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaRSD = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaRSE = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));
  dace::complex128 * __restrict__ sigmaRSF = (dace::complex128*) calloc(((BS * BS) * N), sizeof(dace::complex128));

  __dace_init_rgf_dense(GG, GL, HD, HE, HF, dTGL, fl, fr, gammaleft, gammaright, sigRl, sigRr, sigmaGSD, sigmaGSE, sigmaGSF, sigmaLSD, sigmaLSE, sigmaLSF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);
  __program_rgf_dense(GG, GL, HD, HE, HF, dTGL, fl, fr, gammaleft, gammaright, sigRl, sigRr, sigmaGSD, sigmaGSE, sigmaGSF, sigmaLSD, sigmaLSE, sigmaLSF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);
  __dace_exit_rgf_dense(GG, GL, HD, HE, HF, dTGL, fl, fr, gammaleft, gammaright, sigRl, sigRr, sigmaGSD, sigmaGSE, sigmaGSF, sigmaLSD, sigmaLSE, sigmaLSF, sigmaRSD, sigmaRSE, sigmaRSF, BS, N);

  free(GG);
  free(GL);
  free(HD);
  free(HE);
  free(HF);
  free(dTGL);
  free(fl);
  free(fr);
  free(gammaleft);
  free(gammaright);
  free(sigRl);
  free(sigRr);
  free(sigmaGSD);
  free(sigmaGSE);
  free(sigmaGSF);
  free(sigmaLSD);
  free(sigmaLSE);
  free(sigmaLSF);
  free(sigmaRSD);
  free(sigmaRSE);
  free(sigmaRSF);
  return 0;
}
