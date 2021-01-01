/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void _MatMult__sdfg_0_1_8(dace::complex128* _a, dace::complex128* _b, dace::complex128* _c, int BS) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < BS; _o0 += 1) {
                for (auto _o1 = 0; _o1 < BS; _o1 += 1) {
                    {
                        dace::complex128 out;

                        ///////////////////
                        // Tasklet code (gemm_init)
                        out = 0;
                        ///////////////////

                        _c[((BS * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < BS; __i0 += 1) {
                for (auto __i1 = 0; __i1 < BS; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < BS; __i2 += 1) {
                        {
                            dace::complex128 __a = _a[((BS * __i0) + __i2)];
                            dace::complex128 __b = _b[((BS * __i2) + __i1)];
                            dace::complex128 __out;

                            ///////////////////
                            // Tasklet code (_GEMM_)
                            __out = (__a * __b);
                            ///////////////////

                            dace::wcr_fixed<dace::ReductionType::Sum, dace::complex128>::reduce_atomic(_c + ((BS * __i0) + __i1), __out);
                        }
                    }
                }
            }
        }
    }
    
}

void __program_dTGL_test_internal(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ dTGL, int BS, int N)
{
    long long n;

    for (n = 1; (n < (N - 1)); n = (n + 1)) {
        {
            dace::complex128 *trace_tmp = new dace::complex128 DACE_ALIGN(64)[(BS * BS)];
            
            
            _MatMult__sdfg_0_1_8(&HD[((BS * BS) * n)], &HE[((BS * BS) * n)], &trace_tmp[0], BS);
            {
                #pragma omp parallel for
                for (auto i = 0; i < BS; i += 1) {
                    {
                        dace::complex128 __in2 = trace_tmp[((BS * i) + i)];
                        dace::complex128 __in1 = dTGL[n];
                        dace::complex128 __out;

                        ///////////////////
                        // Tasklet code (augassign_16_12)
                        __out = (__in1 + __in2);
                        ///////////////////

                        dTGL[n] = __out;
                    }
                }
            }
            delete[] trace_tmp;
        }
    }
}

DACE_EXPORTED void __program_dTGL_test(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ dTGL, int BS, int N)
{
    __program_dTGL_test_internal(HD, HE, dTGL, BS, N);
}

DACE_EXPORTED int __dace_init_dTGL_test(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ dTGL, int BS, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_dTGL_test(dace::complex128 * __restrict__ HD, dace::complex128 * __restrict__ HE, dace::complex128 * __restrict__ dTGL, int BS, int N)
{
}

