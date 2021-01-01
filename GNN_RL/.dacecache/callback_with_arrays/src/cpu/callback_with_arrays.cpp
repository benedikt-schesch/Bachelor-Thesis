/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_callback_with_arrays_internal(double * __restrict__ in_arr, double * __restrict__ out_arr, void (*arrfunc)(double const *,double const *), int sym_0, int sym_1, int sym_2)
{

    {
        
        
        {
            double* inp = &in_arr[0];
            double* out = &out_arr[0];

            ///////////////////
            // Tasklet code (callback_59)
            arrfunc(out, inp);
            ///////////////////

        }
    }
}

DACE_EXPORTED void __program_callback_with_arrays(double * __restrict__ in_arr, double * __restrict__ out_arr, void (*arrfunc)(double const *,double const *), int sym_0, int sym_1, int sym_2)
{
    __program_callback_with_arrays_internal(in_arr, out_arr, arrfunc, sym_0, sym_1, sym_2);
}

DACE_EXPORTED int __dace_init_callback_with_arrays(double * __restrict__ in_arr, double * __restrict__ out_arr, void (*arrfunc)(double const *,double const *), int sym_0, int sym_1, int sym_2)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_callback_with_arrays(double * __restrict__ in_arr, double * __restrict__ out_arr, void (*arrfunc)(double const *,double const *), int sym_0, int sym_1, int sym_2)
{
}

