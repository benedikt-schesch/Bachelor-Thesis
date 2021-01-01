/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void reduce_0_0_2(long long* _in, long long* _out) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 10; _o0 += 1) {
                for (auto _o1 = 0; _o1 < 3; _o1 += 1) {
                    {
                        long long out;

                        ///////////////////
                        // Tasklet code (reduce_init)
                        out = (- 9223372036854775808);
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
                                long long inp = _in[(((3 * _i0) + (15 * _o0)) + _o1)];
                                long long out;

                                ///////////////////
                                // Tasklet code (identity)
                                out = inp;
                                ///////////////////

                                dace::wcr_fixed<dace::ReductionType::Max, long long>::reduce(_out + ((3 * _o0) + _o1), out);
                            }
                        }
                    }
                }
            }
        }
    }
    
}

void __program_test_max_int64_internal(long long * __restrict__ A, long long * __restrict__ __return)
{

    {
        
        
        reduce_0_0_2(&A[0], &__return[0]);
    }
}

DACE_EXPORTED void __program_test_max_int64(long long * __restrict__ A, long long * __restrict__ __return)
{
    __program_test_max_int64_internal(A, __return);
}

DACE_EXPORTED int __dace_init_test_max_int64(long long * __restrict__ A, long long * __restrict__ __return)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_max_int64(long long * __restrict__ A, long long * __restrict__ __return)
{
}

