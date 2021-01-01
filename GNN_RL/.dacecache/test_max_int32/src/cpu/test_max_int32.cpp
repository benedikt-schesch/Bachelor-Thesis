/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_0_0_2(int* _in, int* _out) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 10; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 3; _o1 += 1) {
                    {
                        int out;

                        ///////////////////
                        // Tasklet code (reduce_init)
                        out = (- 2147483648);
                        ///////////////////

                        _out[((3 * _o0) + _o1)] = out;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 10; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 3; _o1 += 1) {
                    {
                        for (auto _i0 = 0; _i0 < 5; _i0 += 1) {
                            {
                                int inp = _in[(((3 * _i0) + (15 * _o0)) + _o1)];
                                int out;

                                ///////////////////
                                // Tasklet code (identity)
                                out = inp;
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Max, int>::reduce(_out + ((3 * _o0) + _o1), out);
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void __program_test_max_int32_internal(int * __restrict__ A, int * __restrict__ __return)
{

    {
        
        
        reduce_0_0_2(&A[0], &__return[0]);
    }
}

DACE_EXPORTED void __program_test_max_int32(int * __restrict__ A, int * __restrict__ __return)
{
    __program_test_max_int32_internal(A, __return);
}

DACE_EXPORTED int __dace_init_test_max_int32(int * __restrict__ A, int * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_max_int32(int * __restrict__ A, int * __restrict__ __return)
{
}

