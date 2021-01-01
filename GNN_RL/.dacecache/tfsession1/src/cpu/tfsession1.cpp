/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_tfsession1_internal(int * __restrict__ Const_0, int * __restrict__ Slice_2_0)
{

    {
        
        

        dace::CopyND<int, 1, false, 2, 3>::template ConstDst<3, 1>::Copy(
        Const_0 + 6, Slice_2_0, 6, 1);
    }
}

DACE_EXPORTED void __program_tfsession1(int * __restrict__ Const_0, int * __restrict__ Slice_2_0)
{
    __program_tfsession1_internal(Const_0, Slice_2_0);
}

DACE_EXPORTED int __dace_init_tfsession1(int * __restrict__ Const_0, int * __restrict__ Slice_2_0)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_tfsession1(int * __restrict__ Const_0, int * __restrict__ Slice_2_0)
{
}

