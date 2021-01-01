/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>

#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
#include <chrono>
inline void reduce_0_0_5(double* _in, double* _out, int sym_0) {

    {
        
        
        {
            #pragma omp parallel for
            for (auto _o0 = 0; _o0 < 1; _o0 += 1) {
                {
                    double out;

                    ///////////////////
                    // Tasklet code (reduce_init)
                    out = 0;
                    ///////////////////

                    _out[_o0] = out;
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto _i0 = 0; _i0 < sym_0; _i0 += 1) {
                {
                    double inp = _in[_i0];
                    double out;

                    ///////////////////
                    // Tasklet code (identity)
                    out = inp;
                    ///////////////////

                    dace::wcr_fixed<dace::ReductionType::Sum, double>::reduce_atomic(_out, out);
                }
            }
        }
    }
    
}

void __program_nested_symbol_partial_internal(double * __restrict__ A, int sym_0)
{
    dace::perf::report.reset();

    {
        double *nested_tmp = new double DACE_ALIGN(64)[sym_0];
        
        
        {
            auto __dace_tbegin_0_0_1 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < sym_0; i += 1) {
                {
                    double o;

                    ///////////////////
                    // Tasklet code (nested_12)
                    o = i;
                    ///////////////////

                    nested_tmp[i] = o;
                }
            }
            auto __dace_tend_0_0_1 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_1 = __dace_tend_0_0_1 - __dace_tbegin_0_0_1;
            dace::perf::report.add("timer_Map nested_11", __dace_tdiff_0_0_1.count());
        }
        reduce_0_0_5(&nested_tmp[0], &A[0], sym_0);
        delete[] nested_tmp;
    }
    dace::perf::report.save(".dacecache/nested_symbol_partial/perf");
}

DACE_EXPORTED void __program_nested_symbol_partial(double * __restrict__ A, int sym_0)
{
    __program_nested_symbol_partial_internal(A, sym_0);
}

DACE_EXPORTED int __dace_init_nested_symbol_partial(double * __restrict__ A, int sym_0)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_nested_symbol_partial(double * __restrict__ A, int sym_0)
{
}

