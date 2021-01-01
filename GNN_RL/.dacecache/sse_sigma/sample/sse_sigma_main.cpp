#include <stdlib.h>
#include "sse_sigma.h"

int main(int argc, char** argv) {
  int N3D = 42;
  int NA = 42;
  int NB = 42;
  int NE = 42;
  int Nkz = 42;
  int Norb = 42;
  int Nqz = 42;
  int Nw = 42;
  dace::complex128 * __restrict__ D = (dace::complex128*) calloc((((((N3D * N3D) * NA) * NB) * Nqz) * Nw), sizeof(dace::complex128));
  dace::complex128 * __restrict__ G = (dace::complex128*) calloc((((NA * NE) * Nkz) * (Norb * Norb)), sizeof(dace::complex128));
  dace::complex128 * __restrict__ Sigma = (dace::complex128*) calloc((((NA * NE) * Nkz) * (Norb * Norb)), sizeof(dace::complex128));
  dace::complex128 * __restrict__ dH = (dace::complex128*) calloc((((N3D * NA) * NB) * (Norb * Norb)), sizeof(dace::complex128));
  int * __restrict__ neigh_idx = (int*) calloc((NA * NB), sizeof(int));

  __dace_init_sse_sigma(D, G, Sigma, dH, neigh_idx, N3D, NA, NB, NE, Nkz, Norb, Nqz, Nw);
  __program_sse_sigma(D, G, Sigma, dH, neigh_idx, N3D, NA, NB, NE, Nkz, Norb, Nqz, Nw);
  __dace_exit_sse_sigma(D, G, Sigma, dH, neigh_idx, N3D, NA, NB, NE, Nkz, Norb, Nqz, Nw);

  free(D);
  free(G);
  free(Sigma);
  free(dH);
  free(neigh_idx);
  return 0;
}
