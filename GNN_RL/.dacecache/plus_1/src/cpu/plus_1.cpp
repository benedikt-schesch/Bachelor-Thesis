/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_plus_1_internal(float * __restrict__ X_in, float * __restrict__ X_out, int * __restrict__ num, int N)
{

    {
        
        
        {
            int __p1_e0 = num[0];
            #pragma omp parallel for
            for (auto i = 0; i < __p1_e0; i += 1) {
                {
                    float x_in = X_in[i];
                    float x_out;

                    ///////////////////
                    // Tasklet code (p1)
                    x_out = (x_in + 1);
                    ///////////////////

                    X_out[i] = x_out;
                }
            }
        }
    }
}

DACE_EXPORTED void __program_plus_1(float * __restrict__ X_in, float * __restrict__ X_out, int * __restrict__ num, int N)
{
    __program_plus_1_internal(X_in, X_out, num, N);
}

DACE_EXPORTED int __dace_init_plus_1(float * __restrict__ X_in, float * __restrict__ X_out, int * __restrict__ num, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_plus_1(float * __restrict__ X_in, float * __restrict__ X_out, int * __restrict__ num, int N)
{
}

