/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void test_nested_symbol_type_0_0_1(float* output, float s) {

    {
        
        
        {
            float out;

            ///////////////////
            // Tasklet code (bugs)
            out = s;
            ///////////////////

            output[0] = out;
        }
    }
    
}

void __program_nested_symbol_type_internal(float * __restrict__ data, float s)
{

    {
        
        
        test_nested_symbol_type_0_0_1(&data[0], s);
    }
}

DACE_EXPORTED void __program_nested_symbol_type(float * __restrict__ data, float s)
{
    __program_nested_symbol_type_internal(data, s);
}

DACE_EXPORTED int __dace_init_nested_symbol_type(float * __restrict__ data, float s)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_symbol_type(float * __restrict__ data, float s)
{
}

