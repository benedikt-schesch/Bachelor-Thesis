/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "mkl.h"
#include "../include/dace_blas.h"

void __program_dot_product_MKL_double_internal(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{

    {
        
        
        {
            double* _x = &x[0];
            double* _y = &y[0];
            double* _result = result;

            ///////////////////
            _result = cblas_ddot(n, _x, 1, _y, 1);
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_dot_product_MKL_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    __program_dot_product_MKL_double_internal(result, x, y, n);
}

DACE_EXPORTED int __dace_init_dot_product_MKL_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_dot_product_MKL_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
}

