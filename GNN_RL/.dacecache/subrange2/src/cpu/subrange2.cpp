/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_subrange2_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 3; i += 1) {
                for (auto j = 0; j < 4; j += 1) {
                    float subrange2_22_4___tmp3[1]  DACE_ALIGN(64);
                    {
                        float s1 = A[((4 * i) + j)];
                        float s2 = A[(((4 * i) + j) + 12)];
                        float s3;

                        ///////////////////
                        // Tasklet code (_SSAdd_)
                        s3 = (s1 + s2);
                        ///////////////////

                        subrange2_22_4___tmp3[0] = s3;
                    }
                    {
                        float __inp = subrange2_22_4___tmp3[0];
                        float __out;

                        ///////////////////
                        // Tasklet code (assign_23_8)
                        __out = __inp;
                        ///////////////////

                        B[((4 * i) + j)] = __out;
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_subrange2(float * __restrict__ A, float * __restrict__ B)
{
    __program_subrange2_internal(A, B);
}

DACE_EXPORTED int __dace_init_subrange2(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_subrange2(float * __restrict__ A, float * __restrict__ B)
{
}

