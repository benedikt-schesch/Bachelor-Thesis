/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_nested_loop_test_internal(int * __restrict__ A)
{
    long long j;
    long long i;

    i = 0;
    __state_0_guard_7:;
    if ((! (i < 11))) {
        goto __state_0_endfor_8;
    }
    if ((i < 11)) {
        j = 0;
        goto __state_0_guard;
    }
    __state_0_endfor_8:;
    goto __state_exit_0_sdfg;
    __state_0_guard:;
    if ((j < 5)) {
        goto __state_0_with_10;
    }
    if ((! (j < 5))) {
        i = (i + 1);
        goto __state_0_guard_7;
    }
    __state_0_with_10:;
    {
        
        
        {
            int in_a = A[0];
            int out_a;

            ///////////////////
            // Tasklet code (nested_10)
            out_a = (in_a + 1);
            ///////////////////

            A[0] = out_a;
        }
    }
    j = (j + 1);
    goto __state_0_guard;
    __state_exit_0_sdfg:;
}

DACE_EXPORTED void __program_nested_loop_test(int * __restrict__ A)
{
    __program_nested_loop_test_internal(A);
}

DACE_EXPORTED int __dace_init_nested_loop_test(int * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_loop_test(int * __restrict__ A)
{
}

