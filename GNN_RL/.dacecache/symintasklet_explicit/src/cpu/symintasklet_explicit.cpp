/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_symintasklet_explicit_internal(float * __restrict__ out, float value)
{

    {
        
        
        {
            float o;

            ///////////////////
            // Tasklet code (symintasklet_explicit_15)
            o = value;
            ///////////////////

            out[0] = o;
        }
    }
}

DACE_EXPORTED void __program_symintasklet_explicit(float * __restrict__ out, float value)
{
    __program_symintasklet_explicit_internal(out, value);
}

DACE_EXPORTED int __dace_init_symintasklet_explicit(float * __restrict__ out, float value)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_symintasklet_explicit(float * __restrict__ out, float value)
{
}

