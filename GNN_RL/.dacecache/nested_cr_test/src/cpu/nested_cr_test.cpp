/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

inline void nested_0_0_1(int* nout) {

    {
        
        
        {
            int o;

            ///////////////////
            // Tasklet code (task)
            o = 2;
            ///////////////////

            dace::wcr_fixed<dace::ReductionType::Product, int>::reduce(nout, o);
        }
    }
    
}

void __program_nested_cr_test_internal(int * __restrict__ B)
{

    {
        
        
        nested_0_0_1(&B[0]);
    }
}

DACE_EXPORTED void __program_nested_cr_test(int * __restrict__ B)
{
    __program_nested_cr_test_internal(B);
}

DACE_EXPORTED int __dace_init_nested_cr_test(int * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_cr_test(int * __restrict__ B)
{
}

