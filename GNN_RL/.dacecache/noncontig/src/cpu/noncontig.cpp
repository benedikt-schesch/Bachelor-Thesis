/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void noncontig_internal_0_0_4(float* aA, float* bB) {

    {
        
        
        {
            for (auto i = 0; i < 2; i += 1) {
                for (auto k = 0; k < 4; k += 1) {
                    {
                        float a = aA[((12 * i) + k)];
                        float b;

                        ///////////////////
                        // Tasklet code (dostuff)
                        b = (a * 5);
                        ///////////////////

                        bB[((12 * i) + k)] = b;
                    }
                }
            }
        }
    }
    
}

void __program_noncontig_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto j = 0; j < 3; j += 1) {
                noncontig_internal_0_0_4(&A[(4 * j)], &B[(4 * j)]);
            }
        }
    }
}

DACE_EXPORTED void __program_noncontig(float * __restrict__ A, float * __restrict__ B)
{
    __program_noncontig_internal(A, B);
}

DACE_EXPORTED int __dace_init_noncontig(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_noncontig(float * __restrict__ A, float * __restrict__ B)
{
}

