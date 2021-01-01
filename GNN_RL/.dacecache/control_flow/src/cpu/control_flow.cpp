/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_control_flow_internal(double * __restrict__ A)
{
    long long *__tmp0 = new long long DACE_ALIGN(64)[1];
    long long i;

    {
        
        
        {
            long long out;

            ///////////////////
            // Tasklet code (init___tmp0)
            out = 2;
            ///////////////////

            __tmp0[0] = out;
        }
    }
    if ((! (A[0] < 0.5))) {
        goto __state_0_endif_8;
    }
    if ((A[0] < 0.5)) {
        i = 0;
        goto __state_0_guard;
    }
    __state_0_endif_8:;
    goto __state_0_state_7;
    __state_0_guard:;
    goto __state_0_state_6;
    __state_0_state_7:;
    goto __state_exit_0_sdfg;
    __state_0_state_6:;
    if ((i < 5)) {
        goto __state_0_augassign_10_12;
    }
    if ((! (i < 5))) {
        goto __state_0_endif_8;
    }
    __state_0_augassign_10_12:;
    {
        
        
        {
            double __in1 = A[i];
            long long __in2 = __tmp0[0];
            double __out;

            ///////////////////
            // Tasklet code (augassign_10_12)
            __out = (__in1 * __in2);
            ///////////////////

            A[i] = __out;
        }
    }
    i = (i + 1);
    goto __state_0_guard;
    __state_exit_0_sdfg:;
    delete[] __tmp0;
}

DACE_EXPORTED void __program_control_flow(double * __restrict__ A)
{
    __program_control_flow_internal(A);
}

DACE_EXPORTED int __dace_init_control_flow(double * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_control_flow(double * __restrict__ A)
{
}

