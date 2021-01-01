/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void dot_sdfg_0_0_3(double* _x, double* _y, double* _result, int n) {

    {
        
        
        {
            double _out;

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
                    double __x = _x[__i];
                    double __y = _y[__i];
                    double __out;

                    ///////////////////
                    // Tasklet code (_DOT_)
                    __out = (__x * __y);
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(_result, __out);
                }
            }
        }
    }
    
}

void __program_dot_product_pure_double_internal(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{

    {
        
        
        dot_sdfg_0_0_3(&x[0], &y[0], &result[0], n);
    }
}

DACE_EXPORTED void __program_dot_product_pure_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    __program_dot_product_pure_double_internal(result, x, y, n);
}

DACE_EXPORTED int __dace_init_dot_product_pure_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_dot_product_pure_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
}

