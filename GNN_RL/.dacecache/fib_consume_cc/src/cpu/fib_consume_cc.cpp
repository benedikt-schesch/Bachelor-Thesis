/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_fib_consume_cc_internal(int * __restrict__ iv, float * __restrict__ res)
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
                dace::Consume<2>::template consume_cond(S, 4, [&]() { return (res[0] >= 44); }, [&](int p, const int * __dace_cons_elements, size_t __dace_cons_numelems) {
                    {
                        const int * s = &__dace_cons_elements[0];
                        float val;

                        ///////////////////
                        // Tasklet code (fibonacci)
                        for (auto i : range(__dace_cons_numelems)) {
                            if ((s[i] == 1)) {
                                val = dace::wcr_fixed<dace::ReductionType::Sum, float>::reduce_atomic(res, 1);
                            }
                            else if ((s[i] > 1)) {S.push((s[i] - 1));S.push((s[i] - 2));
                            }
                        }
                        ///////////////////

                    }
                });
            } // End omp section
        } // End omp sections
    }
}

DACE_EXPORTED void __program_fib_consume_cc(int * __restrict__ iv, float * __restrict__ res)
{
    __program_fib_consume_cc_internal(iv, res);
}

DACE_EXPORTED int __dace_init_fib_consume_cc(int * __restrict__ iv, float * __restrict__ res)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_fib_consume_cc(int * __restrict__ iv, float * __restrict__ res)
{
}

