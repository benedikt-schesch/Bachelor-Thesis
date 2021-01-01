/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_fusion_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ out)
{

    {
        float *tmp = new float DACE_ALIGN(64)[200];
        float *tmp_2 = new float DACE_ALIGN(64)[200];
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 10; i += 1) {
                for (auto j = 0; j < 20; j += 1) {
                    {
                        float a = A[((20 * i) + j)];
                        float b;

                        ///////////////////
                        // Tasklet code (fusion_14)
                        b = (a * a);
                        ///////////////////

                        tmp[((20 * i) + j)] = b;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                for (auto j = 0; j < 10; j += 1) {
                    {
                        float a = tmp[(i + (20 * j))];
                        float b = B[(i + (20 * j))];
                        float c;

                        ///////////////////
                        // Tasklet code (fusion_21)
                        c = (a + b);
                        ///////////////////

                        tmp_2[(i + (20 * j))] = c;
                    }
                }
            }
        }
        {
            #pragma omp parallel for
            for (auto m = 0; m < 10; m += 1) {
                for (auto n = 0; n < 20; n += 1) {
                    {
                        float a = tmp_2[((20 * m) + n)];
                        float b;

                        ///////////////////
                        // Tasklet code (fusion_29)
                        b = a;
                        ///////////////////

                        dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(out, b);
                    }
                }
            }
        }
        delete[] tmp;
        delete[] tmp_2;
    }
}

DACE_EXPORTED void __program_fusion(float * __restrict__ A, float * __restrict__ B, float * __restrict__ out)
{
    __program_fusion_internal(A, B, out);
}

DACE_EXPORTED int __dace_init_fusion(float * __restrict__ A, float * __restrict__ B, float * __restrict__ out)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_fusion(float * __restrict__ A, float * __restrict__ B, float * __restrict__ out)
{
}

