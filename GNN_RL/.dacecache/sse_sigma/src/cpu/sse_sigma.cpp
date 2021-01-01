/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void _MatMult__sdfg_1_0_0_21(dace::complex128* _a, dace::complex128* _b, dace::complex128* _c, int Norb) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < Norb; _o0 += 1) {
                for (auto _o1 = 0; _o1 < Norb; _o1 += 1) {
                    {
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((Norb * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto __i0 = 0; __i0 < Norb; __i0 += 1) {
                for (auto __i1 = 0; __i1 < Norb; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < Norb; __i2 += 1) {
                        {
                            dace::complex128 __a = _a[((Norb * __i0) + __i2)];
                            dace::complex128 __b = _b[((Norb * __i2) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, dace::complex128>::reduce(_c + ((Norb * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

inline void _MatMult__sdfg_0_0_22(dace::complex128* _a, dace::complex128* _b, dace::complex128* _c, int Norb) {

    {
        
        
        {
            for (auto _o0 = 0; _o0 < Norb; _o0 += 1) {
                for (auto _o1 = 0; _o1 < Norb; _o1 += 1) {
                    {
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((Norb * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            for (auto __i0 = 0; __i0 < Norb; __i0 += 1) {
                for (auto __i1 = 0; __i1 < Norb; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < Norb; __i2 += 1) {
                        {
                            dace::complex128 __a = _a[((Norb * __i0) + __i2)];
                            dace::complex128 __b = _b[((Norb * __i2) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, dace::complex128>::reduce(_c + ((Norb * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_sse_sigma_internal(dace::complex128 * __restrict__ D, dace::complex128 * __restrict__ G, dace::complex128 * __restrict__ Sigma, dace::complex128 * __restrict__ dH, int * __restrict__ neigh_idx, int N3D, int NA, int NB, int NE, int Nkz, int Norb, int Nqz, int Nw)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto k = 0; k < Nkz; k += 1) {
                for (auto E = 0; E < NE; E += 1) {
                    for (auto q = 0; q < Nqz; q += 1) {
                        for (auto w = 0; w < Nw; w += 1) {
                            for (auto i = 0; i < N3D; i += 1) {
                                for (auto j = 0; j < N3D; j += 1) {
                                    for (auto a = 0; a < NA; a += 1) {
                                        for (auto b = 0; b < NB; b += 1) {
                                            dace::complex128 *____tmp_22_14_r_value = new dace::complex128 DACE_ALIGN(64)[(Norb * Norb)];
                                            dace::complex128 *sse_sigma_19_4_dHD = new dace::complex128 DACE_ALIGN(64)[(Norb * Norb)];
                                            dace::complex128 *sse_sigma_19_4_dHG = new dace::complex128 DACE_ALIGN(64)[(Norb * Norb)];
                                            dace::complex128 *sse_sigma_19_4___tmp3 = new dace::complex128 DACE_ALIGN(64)[(Norb * Norb)];
                                            {
                                                for (auto __i0 = 0; __i0 < Norb; __i0 += 1) {
                                                    for (auto __i1 = 0; __i1 < Norb; __i1 += 1) {
                                                        {
                                                            int index_neigh_idx_0 = neigh_idx[((NB * a) + b)];
                                                            dace::complex128* __ind___tmp_22_14_r = &G[0];
                                                            dace::complex128 lookup;

                                                            ///////////////////
                                                            // Tasklet code (Indirection)
                                                            lookup = __ind___tmp_22_14_r[(((((((NA * NE) * (Norb * Norb)) * (k - q)) + ((NA * (Norb * Norb)) * (E - w))) + ((Norb * Norb) * index_neigh_idx_0)) + (Norb * __i0)) + __i1)];
                                                            ///////////////////

                                                            ____tmp_22_14_r_value[((Norb * __i0) + __i1)] = lookup;
                                                        }
                                                    }
                                                }
                                            }
                                            _MatMult__sdfg_1_0_0_21(&____tmp_22_14_r_value[0], &dH[(((((N3D * NB) * (Norb * Norb)) * a) + ((N3D * (Norb * Norb)) * b)) + ((Norb * Norb) * i))], &sse_sigma_19_4_dHG[0], Norb);
                                            {
                                                for (auto __i0 = 0; __i0 < Norb; __i0 += 1) {
                                                    for (auto __i1 = 0; __i1 < Norb; __i1 += 1) {
                                                        {
                                                            dace::complex128 __in1 = dH[(((((((N3D * NB) * (Norb * Norb)) * a) + ((N3D * (Norb * Norb)) * b)) + ((Norb * Norb) * j)) + (Norb * __i0)) + __i1)];
                                                            dace::complex128 __in2 = D[((((((((((N3D * N3D) * NA) * NB) * Nw) * q) + ((((N3D * N3D) * NA) * NB) * w)) + (((N3D * N3D) * NB) * a)) + ((N3D * N3D) * b)) + (N3D * i)) + j)];
                                                            dace::complex128 __out;

                                                            ///////////////////
                                                            // Tasklet code (_Mult_)
                                                            __out = (__in1 * __in2);
                                                            ///////////////////

                                                            sse_sigma_19_4_dHD[((Norb * __i0) + __i1)] = __out;
                                                        }
                                                    }
                                                }
                                            }
                                            _MatMult__sdfg_0_0_22(&sse_sigma_19_4_dHG[0], &sse_sigma_19_4_dHD[0], &sse_sigma_19_4___tmp3[0], Norb);
                                            {
                                                for (auto __i0 = 0; __i0 < Norb; __i0 += 1) {
                                                    for (auto __i1 = 0; __i1 < Norb; __i1 += 1) {
                                                        {
                                                            dace::complex128 __in2 = sse_sigma_19_4___tmp3[((Norb * __i0) + __i1)];
                                                            dace::complex128 __in1 = Sigma[((((((E * NA) * (Norb * Norb)) + (((NA * NE) * (Norb * Norb)) * k)) + ((Norb * Norb) * a)) + (Norb * __i0)) + __i1)];
                                                            dace::complex128 __out;

                                                            ///////////////////
                                                            // Tasklet code (augassign_24_8)
                                                            __out = (__in1 + __in2);
                                                            ///////////////////

                                                            Sigma[((((((E * NA) * (Norb * Norb)) + (((NA * NE) * (Norb * Norb)) * k)) + ((Norb * Norb) * a)) + (Norb * __i0)) + __i1)] = __out;
                                                        }
                                                    }
                                                }
                                            }
                                            delete[] ____tmp_22_14_r_value;
                                            delete[] sse_sigma_19_4_dHD;
                                            delete[] sse_sigma_19_4_dHG;
                                            delete[] sse_sigma_19_4___tmp3;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_sse_sigma(dace::complex128 * __restrict__ D, dace::complex128 * __restrict__ G, dace::complex128 * __restrict__ Sigma, dace::complex128 * __restrict__ dH, int * __restrict__ neigh_idx, int N3D, int NA, int NB, int NE, int Nkz, int Norb, int Nqz, int Nw)
{
    __program_sse_sigma_internal(D, G, Sigma, dH, neigh_idx, N3D, NA, NB, NE, Nkz, Norb, Nqz, Nw);
}

DACE_EXPORTED int __dace_init_sse_sigma(dace::complex128 * __restrict__ D, dace::complex128 * __restrict__ G, dace::complex128 * __restrict__ Sigma, dace::complex128 * __restrict__ dH, int * __restrict__ neigh_idx, int N3D, int NA, int NB, int NE, int Nkz, int Norb, int Nqz, int Nw)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_sse_sigma(dace::complex128 * __restrict__ D, dace::complex128 * __restrict__ G, dace::complex128 * __restrict__ Sigma, dace::complex128 * __restrict__ dH, int * __restrict__ neigh_idx, int N3D, int NA, int NB, int NE, int Nkz, int Norb, int Nqz, int Nw)
{
}

