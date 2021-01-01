/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_0_0_2(float* _in, float* _out) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    float out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = 9999999;
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < 20; _i0 += 1) {
                {
                    float inp = _in[_i0];
                    float out;

                    ///////////////////
                    // Tasklet code (identity)
                    out = inp;
                    ///////////////////

                    dace::wcr_custom<float>:: template reduce_atomic([] (const float& a, const float& b) { return ((a < b) ? a : b); }, _out, out);
                }
            }
        }
    }
    
}

void __program_customreduction_internal(float * __restrict__ A, float * __restrict__ out)
{

    {
        
        
        reduce_0_0_2(&A[0], &out[0]);
    }
}

DACE_EXPORTED void __program_customreduction(float * __restrict__ A, float * __restrict__ out)
{
    __program_customreduction_internal(A, out);
}

DACE_EXPORTED int __dace_init_customreduction(float * __restrict__ A, float * __restrict__ out)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_customreduction(float * __restrict__ A, float * __restrict__ out)
{
}

