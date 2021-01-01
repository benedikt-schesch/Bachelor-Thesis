/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void nested_0_0_2(dace::ArrayStreamView<int>& nout) {

    {
        
        
        {

            ///////////////////
            // Tasklet code (task)
            nout.push(2);
            ///////////////////

        }
    }
    
}

void __program_nested_stream_test_internal(int * __restrict__ B)
{

    {
        dace::ArrayStreamView<int> SB (B);
        
        
        nested_0_0_2(SB);
    }
}

DACE_EXPORTED void __program_nested_stream_test(int * __restrict__ B)
{
    __program_nested_stream_test_internal(B);
}

DACE_EXPORTED int __dace_init_nested_stream_test(int * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_stream_test(int * __restrict__ B)
{
}

