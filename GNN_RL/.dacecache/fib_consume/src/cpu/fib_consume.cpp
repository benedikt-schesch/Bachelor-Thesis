/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_fib_consume_internal(int * __restrict__ iv, float * __restrict__ res)
{

    {
        dace::Stream<int> S(1);
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                S.push(iv, 1);
            } // End omp section
            #pragma omp section
            {
                dace::Consume<1>::template consume(S, 4, [&](int p, const int& __dace_cons_element) {
                    {
                        int s = __dace_cons_element;
                        float val;

                        ///////////////////
                        // Tasklet code (fibonacci)
                        if ((s == 1)) {
                            val = dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(res, 1);
                        }
                        else if ((s > 1)) {S.push((s - 1));S.push((s - 2));
                        }
                        ///////////////////

                    }
                });
            } // End omp section
        } // End omp sections
    }
}

DACE_EXPORTED void __program_fib_consume(int * __restrict__ iv, float * __restrict__ res)
{
    __program_fib_consume_internal(iv, res);
}

DACE_EXPORTED int __dace_init_fib_consume(int * __restrict__ iv, float * __restrict__ res)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_fib_consume(int * __restrict__ iv, float * __restrict__ res)
{
}

