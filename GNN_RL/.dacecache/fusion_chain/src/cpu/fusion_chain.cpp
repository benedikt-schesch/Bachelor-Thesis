/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_fusion_chain_internal(float * __restrict__ A, float * __restrict__ B)
{
    long long *__tmp0 = new long long DACE_ALIGN(64)[1];
    long long *__tmp2 = new long long DACE_ALIGN(64)[1];
    long long *__tmp4 = new long long DACE_ALIGN(64)[1];

    {
        float *tmp1 = new float DACE_ALIGN(64)[200];
        float *tmp2 = new float DACE_ALIGN(64)[200];
        
        
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp0)
            out = 2;
            ///////////////////

            __tmp0[0] = out;
        }
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp2)
            out = 4;
            ///////////////////

            __tmp2[0] = out;
        }
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp4)
            out = 5;
            ///////////////////

            __tmp4[0] = out;
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 10; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 20; __i1 += 1) {
                    {
                        float __in1 = A[((20 * __i0) + __i1)];
                        long long __in2 = __tmp0[0];
                        float __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        tmp1[((20 * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 10; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 20; __i1 += 1) {
                    {
                        float __in1 = tmp1[((20 * __i0) + __i1)];
                        long long __in2 = __tmp2[0];
                        float __out;

                        ///////////////////
                        // Tasklet code (_Mult_)
                        __out = (__in1 * __in2);
                        ///////////////////

                        tmp2[((20 * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 10; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 20; __i1 += 1) {
                    {
                        float __in1 = tmp2[((20 * __i0) + __i1)];
                        long long __in2 = __tmp4[0];
                        float __out;

                        ///////////////////
                        // Tasklet code (_Add_)
                        __out = (__in1 + __in2);
                        ///////////////////

                        B[((20 * __i0) + __i1)] = __out;
                    }
                }
            }
        }
        delete[] tmp1;
        delete[] tmp2;
    }
    delete[] __tmp0;
    delete[] __tmp2;
    delete[] __tmp4;
}

DACE_EXPORTED void __program_fusion_chain(float * __restrict__ A, float * __restrict__ B)
{
    __program_fusion_chain_internal(A, B);
}

DACE_EXPORTED int __dace_init_fusion_chain(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_fusion_chain(float * __restrict__ A, float * __restrict__ B)
{
}

