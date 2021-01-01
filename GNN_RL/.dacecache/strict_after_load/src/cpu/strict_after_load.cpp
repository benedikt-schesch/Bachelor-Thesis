/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_strict_after_load_internal(float * __restrict__ A, float * __restrict__ B)
{
    long long strict_after_load_8_4___tmp1[1]  DACE_ALIGN(64);

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 10; i += 1) {
                for (auto j = 0; j < 20; j += 1) {
                    float strict_after_load_8_4___tmp2[1]  DACE_ALIGN(64);
                    {
                        long long out;

                        ///////////////////
                        // Tasklet code (init___tmp1)
                        out = 1;
                        ///////////////////

                        strict_after_load_8_4___tmp1[0] = out;
                    }
                    {
                        long long s2 = strict_after_load_8_4___tmp1[0];
                        float s1 = A[((20 * i) + j)];
                        float s3;

                        ///////////////////
                        // Tasklet code (_SSAdd_)
                        s3 = (s1 + s2);
                        ///////////////////

                        strict_after_load_8_4___tmp2[0] = s3;
                    }
                    {
                        float __inp = strict_after_load_8_4___tmp2[0];
                        float __out;

                        ///////////////////
                        // Tasklet code (assign_9_8)
                        __out = __inp;
                        ///////////////////

                        B[((20 * i) + j)] = __out;
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_strict_after_load(float * __restrict__ A, float * __restrict__ B)
{
    __program_strict_after_load_internal(A, B);
}

DACE_EXPORTED int __dace_init_strict_after_load(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_strict_after_load(float * __restrict__ A, float * __restrict__ B)
{
}

