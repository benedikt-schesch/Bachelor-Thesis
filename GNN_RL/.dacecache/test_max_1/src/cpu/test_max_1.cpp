/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_test_max_1_internal(double * __restrict__ A, double * __restrict__ __return)
{

    {
        
        
        {
            double* _in = &A[0];
            double* _out = __return;

            ///////////////////
            #pragma omp parallel for collapse(2)
            for (int _o0 = 0; _o0 < 10; ++_o0) {
                for (int _o1 = 0; _o1 < 3; ++_o1) {
                    _out[_o0 * 3 + _o1 * 1] = -1.7976931348623157e+308;
                    #pragma omp parallel for collapse(1) reduction(max: _out[_o0 * 3 + _o1 * 1])
                    for (int _i0 = 0; _i0 < 5; ++_i0) {
                        _out[_o0 * 3 + _o1 * 1] = max(_out[_o0 * 3 + _o1 * 1], _in[_o0 * 15 + _i0 * 3 + _o1 * 1]);
                    }
                }
            }
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_test_max_1(double * __restrict__ A, double * __restrict__ __return)
{
    __program_test_max_1_internal(A, __return);
}

DACE_EXPORTED int __dace_init_test_max_1(double * __restrict__ A, double * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_max_1(double * __restrict__ A, double * __restrict__ __return)
{
}

