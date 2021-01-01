extern "C" int __dace_init_sse_sigma(dace::complex128 * __restrict__ D, dace::complex128 * __restrict__ G, dace::complex128 * __restrict__ Sigma, dace::complex128 * __restrict__ dH, int * __restrict__ neigh_idx, int N3D, int NA, int NB, int NE, int Nkz, int Norb, int Nqz, int Nw);
extern "C" int __dace_exit_sse_sigma(dace::complex128 * __restrict__ D, dace::complex128 * __restrict__ G, dace::complex128 * __restrict__ Sigma, dace::complex128 * __restrict__ dH, int * __restrict__ neigh_idx, int N3D, int NA, int NB, int NE, int Nkz, int Norb, int Nqz, int Nw);
extern "C" void __program_sse_sigma(dace::complex128 * __restrict__ D, dace::complex128 * __restrict__ G, dace::complex128 * __restrict__ Sigma, dace::complex128 * __restrict__ dH, int * __restrict__ neigh_idx, int N3D, int NA, int NB, int NE, int Nkz, int Norb, int Nqz, int Nw);