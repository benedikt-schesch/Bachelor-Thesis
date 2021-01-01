/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

struct pair {
    int idx;
    double val;
};
void __program_argmax_internal(pair * __restrict__ __return, double * __restrict__ x)
{

    {
        
        
        {
            pair init;

            ///////////////////
            // Tasklet code (argmax_11)
            init.idx = (- 1);
            init.val = (- 1e+38);
            ///////////////////

            __return[0] = init;
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 1024; i += 1) {
                {
                    double inp = x[i];
                    pair out;

                    ///////////////////
                    // Tasklet code (argmax_17)
                    out = pair { .idx = i, .val = inp };
                    ///////////////////

                    dace::wcr_custom<pair>:: template reduce_atomic([] (const pair& x, const pair& y) { return pair { .idx = ((x.val > y.val) ? x.idx : y.idx), .val = max(x.val, y.val) }; }, __return, out);
                }
            }
        }
    }
}

DACE_EXPORTED void __program_argmax(pair * __restrict__ __return, double * __restrict__ x)
{
    __program_argmax_internal(__return, x);
}

DACE_EXPORTED int __dace_init_argmax(pair * __restrict__ __return, double * __restrict__ x)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_argmax(pair * __restrict__ __return, double * __restrict__ x)
{
}

