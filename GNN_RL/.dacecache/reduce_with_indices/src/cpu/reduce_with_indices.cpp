/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_0_0_2(double* _in, double* _out) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < 1; _i0 += 1) {
                for (auto _i1 = 0; _i1 < 1; _i1 += 1) {
                    for (auto _i2 = 0; _i2 < 1; _i2 += 1) {
                        for (auto _i3 = 0; _i3 < 10; _i3 += 1) {
                            {
                                double inp = _in[((((1000 * _i0) + (100 * _i1)) + (10 * _i2)) + _i3)];
                                double out;

                                ///////////////////
                                // Tasklet code (identity)
                                out = inp;
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Max, double>::reduce_atomic(_out, out);
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void __program_reduce_with_indices_internal(double * __restrict__ A, double * __restrict__ B)
{

    {
        
        
        reduce_0_0_2(&A[120], &B[0]);
    }
}

DACE_EXPORTED void __program_reduce_with_indices(double * __restrict__ A, double * __restrict__ B)
{
    __program_reduce_with_indices_internal(A, B);
}

DACE_EXPORTED int __dace_init_reduce_with_indices(double * __restrict__ A, double * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_reduce_with_indices(double * __restrict__ A, double * __restrict__ B)
{
}

