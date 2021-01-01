/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void subrange_of_subrange_nested_39_4_0_0_2(float* __tmp_40_15_r, float* __tmp_40_8_w, long long k) {

    {
        
        

        dace::CopyND<float, 1, false, 4>::template ConstDst<1>::Copy(
        __tmp_40_15_r + (60 * k), __tmp_40_8_w, 5);
    }
    
}

void __program_subrange_of_subrange_nested_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 3; i += 1) {
                for (auto j = 0; j < 5; j += 1) {
                    for (auto k = 0; k < 2; k += 1) {
                        subrange_of_subrange_nested_39_4_0_0_2(&A[((20 * i) + j)], &B[0], k);
                    }
                }
            }
        }
    }
}

DACE_EXPORTED void __program_subrange_of_subrange_nested(float * __restrict__ A, float * __restrict__ B)
{
    __program_subrange_of_subrange_nested_internal(A, B);
}

DACE_EXPORTED int __dace_init_subrange_of_subrange_nested(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_subrange_of_subrange_nested(float * __restrict__ A, float * __restrict__ B)
{
}

