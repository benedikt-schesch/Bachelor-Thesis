/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_vla_test_internal(float * __restrict__ A, float * __restrict__ B, int N)
{

    {
        float *tmp = new float DACE_ALIGN(64)[N];
        
        

        dace::CopyNDDynamic<float, 1, false, 1>::template ConstDst<1>::Copy(
        A, tmp, N, 1);

        dace::CopyNDDynamic<float, 1, false, 1>::template ConstDst<1>::Copy(
        tmp, B, N, 1);
        delete[] tmp;
    }
}

DACE_EXPORTED void __program_vla_test(float * __restrict__ A, float * __restrict__ B, int N)
{
    __program_vla_test_internal(A, B, N);
}

DACE_EXPORTED int __dace_init_vla_test(float * __restrict__ A, float * __restrict__ B, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_vla_test(float * __restrict__ A, float * __restrict__ B, int N)
{
}

