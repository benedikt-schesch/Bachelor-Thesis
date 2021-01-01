/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

void __program_reassign_internal(double * __restrict__ a)
{
    double *s = new double DACE_ALIGN(64)[1];
    double *__tmp1 = new double DACE_ALIGN(64)[1];

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    double out;

                    ///////////////////
                    // Tasklet code (init___tmp0)
                    out = 0.0;
                    ///////////////////

                    s[0] = out;
                }
            } // End omp section
            #pragma omp section
            {
                {
                    double out;

                    ///////////////////
                    // Tasklet code (init___tmp1)
                    out = 1.0;
                    ///////////////////

                    __tmp1[0] = out;
                }
            } // End omp section
        } // End omp sections
    }
    {
        
        
        {
            double __inp = __tmp1[0];
            double __out;

            ///////////////////
            // Tasklet code (assign_8_4)
            __out = __inp;
            ///////////////////

            s[0] = __out;
        }
        {
            double __inp = s[0];
            double __out;

            ///////////////////
            // Tasklet code (assign_9_4)
            __out = __inp;
            ///////////////////

            a[0] = __out;
        }
    }
    delete[] s;
    delete[] __tmp1;
}

DACE_EXPORTED void __program_reassign(double * __restrict__ a)
{
    __program_reassign_internal(a);
}

DACE_EXPORTED int __dace_init_reassign(double * __restrict__ a)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_reassign(double * __restrict__ a)
{
}

