/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_test_sum_internal(double * __restrict__ A, double * __restrict__ __return)
{

    {
        
        
        {
            double* _in = &A[0];
            double* _out = __return;

            ///////////////////
            _out[0] = 0;
            #pragma omp parallel for collapse(3) reduction(+: _out[0])
            for (int _i0 = 0; _i0 < 10; ++_i0) {
                for (int _i1 = 0; _i1 < 5; ++_i1) {
                    for (int _i2 = 0; _i2 < 3; ++_i2) {
                        _out[0] += _in[_i0 * 15 + _i1 * 3 + _i2 * 1];
                    }
                }
            }
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_test_sum(double * __restrict__ A, double * __restrict__ __return)
{
    __program_test_sum_internal(A, __return);
}

DACE_EXPORTED int __dace_init_test_sum(double * __restrict__ A, double * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_sum(double * __restrict__ A, double * __restrict__ __return)
{
}

