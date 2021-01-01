/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void dot_sdfg_0_0_3(float* _x, float* _y, float* _result, int n) {

    {
        
        
        {
            float _out;

            ///////////////////
            // Tasklet code (dot_init)
            _out = 0;
            ///////////////////

            _result[0] = _out;
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i = 0; __i < n; __i += 1) {
                {
                    float __x = _x[__i];
                    float __y = _y[__i];
                    float __out;

                    ///////////////////
                    // Tasklet code (_DOT_)
                    __out = (__x * __y);
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(_result, __out);
                }
            }
        }
    }
    
}

void __program_dot_product_pure_float_internal(float * __restrict__ result, float * __restrict__ x, float * __restrict__ y, int n)
{

    {
        
        
        dot_sdfg_0_0_3(&x[0], &y[0], &result[0], n);
    }
}

DACE_EXPORTED void __program_dot_product_pure_float(float * __restrict__ result, float * __restrict__ x, float * __restrict__ y, int n)
{
    __program_dot_product_pure_float_internal(result, x, y, n);
}

DACE_EXPORTED int __dace_init_dot_product_pure_float(float * __restrict__ result, float * __restrict__ x, float * __restrict__ y, int n)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_dot_product_pure_float(float * __restrict__ result, float * __restrict__ x, float * __restrict__ y, int n)
{
}

