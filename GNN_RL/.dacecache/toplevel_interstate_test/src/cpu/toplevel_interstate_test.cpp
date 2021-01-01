/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_toplevel_interstate_test_internal()
{
    int *tmp = new int DACE_ALIGN(64)[1];

    {
        
        
        {
            int t;

            ///////////////////
            // Tasklet code (settmp)
            t = 5;
            ///////////////////

            tmp[0] = t;
        }
    }
    if ((tmp[0] > 2)) {
        goto __state_0_state_1;
    }
    if ((tmp[0] <= 2)) {
        goto __state_0_state_2;
    }
    __state_0_state_1:;
    {
        
        
        {

            ///////////////////
            // Tasklet code (sayhi)
            printf("OK\n");
            ///////////////////

        }
    }
    goto __state_exit_0_sdfg;
    __state_0_state_2:;
    {
        
        
        {

            ///////////////////
            // Tasklet code (saybye)
            printf("FAIL\n");
            ///////////////////

        }
    }
    __state_exit_0_sdfg:;
    delete[] tmp;
}

DACE_EXPORTED void __program_toplevel_interstate_test()
{
    __program_toplevel_interstate_test_internal();
}

DACE_EXPORTED int __dace_init_toplevel_interstate_test()
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_toplevel_interstate_test()
{
}

