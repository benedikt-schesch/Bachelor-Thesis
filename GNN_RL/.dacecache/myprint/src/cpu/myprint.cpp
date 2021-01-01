/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_myprint_internal(float * __restrict__ input, long long M, long long N)
{

    {
        
        
        {
            float* a = &input[0];

            ///////////////////
            // Tasklet code (myprint)
            for (auto i : range(0, N)) {
                for (auto j : range(0, M)) {
                    printf("%f\n", dace::math::sin(a[((10 * i) + j)]));
                }
            }
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_myprint(float * __restrict__ input, long long M, long long N)
{
    __program_myprint_internal(input, M, N);
}

DACE_EXPORTED int __dace_init_myprint(float * __restrict__ input, long long M, long long N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_myprint(float * __restrict__ input, long long M, long long N)
{
}

