/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_stiledcopy_internal(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {

                dace::CopyND<float, 1, false, 2, 2>::template ConstDst<2, 1>::Copy(
                A + 67, B, 32, 4);

                dace::CopyND<float, 1, false, 2, 2>::template ConstDst<32, 4>::Copy(
                B, C + 67, 2, 1);
            } // End omp section
            #pragma omp section
            {

                dace::CopyND<float, 1, false, 2, 2, 4, 4>::template ConstDst<32, 4, 8, 1>::Copy(
                D + 1028, E, 8192, 64, 128, 1);

                dace::CopyND<float, 1, false, 2, 2, 4, 4>::template ConstDst<8192, 64, 128, 1>::Copy(
                E, F + 1028, 32, 4, 8, 1);
            } // End omp section
        } // End omp sections
    }
}

DACE_EXPORTED void __program_stiledcopy(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{
    __program_stiledcopy_internal(A, B, C, D, E, F);
}

DACE_EXPORTED int __dace_init_stiledcopy(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_stiledcopy(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float * __restrict__ D, float * __restrict__ E, float * __restrict__ F)
{
}

