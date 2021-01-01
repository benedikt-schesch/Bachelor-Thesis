/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_subrange_of_subrange_internal(float * __restrict__ A, float * __restrict__ B)
{

    {
        
        

        dace::CopyND<float, 1, false, 4>::template ConstDst<1>::Copy(
        A, B, 5);
    }
}

DACE_EXPORTED void __program_subrange_of_subrange(float * __restrict__ A, float * __restrict__ B)
{
    __program_subrange_of_subrange_internal(A, B);
}

DACE_EXPORTED int __dace_init_subrange_of_subrange(float * __restrict__ A, float * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_subrange_of_subrange(float * __restrict__ A, float * __restrict__ B)
{
}

