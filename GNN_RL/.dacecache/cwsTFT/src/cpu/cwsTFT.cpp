/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_cwsTFT_internal(double * __restrict__ A, double * __restrict__ B, int W, int X, int Y, int Z)
{

    {
        
        

        dace::CopyND<double, 1, false, 2, 3, 4, 5>::template ConstSrc<120, 10, 30, 2>::Copy(
        A, B, X, Y, Z, W);
    }
}

DACE_EXPORTED void __program_cwsTFT(double * __restrict__ A, double * __restrict__ B, int W, int X, int Y, int Z)
{
    __program_cwsTFT_internal(A, B, W, X, Y, Z);
}

DACE_EXPORTED int __dace_init_cwsTFT(double * __restrict__ A, double * __restrict__ B, int W, int X, int Y, int Z)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_cwsTFT(double * __restrict__ A, double * __restrict__ B, int W, int X, int Y, int Z)
{
}

