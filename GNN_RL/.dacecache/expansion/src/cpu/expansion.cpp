/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_expansion_internal(float * __restrict__ A, int * __restrict__ rng)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                {
                    int __mymap_b0 = rng[0];
                    int __mymap_e0 = rng[1];
                    for (auto j = __mymap_b0; j < __mymap_e0; j += 1) {
                        {
                            for (auto k = 0; k < 5; k += 1) {
                                {
                                    float a = A[(((150 * i) + (5 * j)) + k)];
                                    float b;

                                    ///////////////////
                                    // Tasklet code (mymap)
                                    b = (a * 2);
                                    ///////////////////

                                    A[(((150 * i) + (5 * j)) + k)] = b;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_expansion(float * __restrict__ A, int * __restrict__ rng)
{
    __program_expansion_internal(A, rng);
}

DACE_EXPORTED int __dace_init_expansion(float * __restrict__ A, int * __restrict__ rng)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_expansion(float * __restrict__ A, int * __restrict__ rng)
{
}

