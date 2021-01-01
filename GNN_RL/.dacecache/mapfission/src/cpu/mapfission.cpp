/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_mapfission_internal(double * __restrict__ A, double * __restrict__ B)
{
    dace::perf::report.reset();

    {
        double *s2 = new double DACE_ALIGN(64)[4];
        double *s3out = new double DACE_ALIGN(64)[2];
        double *s1 = new double DACE_ALIGN(64)[2];
        double *scal = new double DACE_ALIGN(64)[2];
        
        
        {
            auto __dace_tbegin_0_0_15 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                {
                    double* a = &A[(2 * i)];
                    double b;

                    ///////////////////
                    // Tasklet code (one)
                    b = (a[0] + a[1]);
                    ///////////////////

                    s1[i] = b;
                }
            }
            auto __dace_tend_0_0_15 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_15 = __dace_tend_0_0_15 - __dace_tbegin_0_0_15;
            dace::perf::report.add("timer_Map outer_fission", __dace_tdiff_0_0_15.count());
        }
        {
            auto __dace_tbegin_0_0_17 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                {
                    auto __dace_tbegin_0_0_2 = std::chrono::high_resolution_clock::now();
                    for (auto j = 0; j < 2; j += 1) {
                        {
                            double a = A[((2 * i) + j)];
                            double b;

                            ///////////////////
                            // Tasklet code (two)
                            b = (a * 2);
                            ///////////////////

                            s2[((2 * i) + j)] = b;
                        }
                    }
                    auto __dace_tend_0_0_2 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_2 = __dace_tend_0_0_2 - __dace_tbegin_0_0_2;
                    dace::perf::report.add("timer_Map inner", __dace_tdiff_0_0_2.count());
                }
            }
            auto __dace_tend_0_0_17 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_17 = __dace_tend_0_0_17 - __dace_tbegin_0_0_17;
            dace::perf::report.add("timer_Map outer_fission", __dace_tdiff_0_0_17.count());
        }
        {
            auto __dace_tbegin_0_0_19 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                {
                    auto __dace_tbegin_0_0_7 = std::chrono::high_resolution_clock::now();
                    for (auto j = 0; j < 2; j += 1) {
                        {
                            double* a = &A[(2 * i)];
                            double b;

                            ///////////////////
                            // Tasklet code (three)
                            b = (a[0] * 3);
                            ///////////////////

                            s3out[i] = b;
                        }
                    }
                    auto __dace_tend_0_0_7 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_7 = __dace_tend_0_0_7 - __dace_tbegin_0_0_7;
                    dace::perf::report.add("timer_Map inner", __dace_tdiff_0_0_7.count());
                }
            }
            auto __dace_tend_0_0_19 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_19 = __dace_tend_0_0_19 - __dace_tbegin_0_0_19;
            dace::perf::report.add("timer_Map outer_fission", __dace_tdiff_0_0_19.count());
        }
        {
            auto __dace_tbegin_0_0_21 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                {
                    double out;

                    ///////////////////
                    // Tasklet code (scalar)
                    out = 5.0;
                    ///////////////////

                    scal[i] = out;
                }
            }
            auto __dace_tend_0_0_21 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_21 = __dace_tend_0_0_21 - __dace_tbegin_0_0_21;
            dace::perf::report.add("timer_Map outer_fission", __dace_tdiff_0_0_21.count());
        }
        {
            auto __dace_tbegin_0_0_23 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 2; i += 1) {
                {
                    double* itwo = &s2[(2 * i)];
                    double ithree = s3out[i];
                    double ione = s1[i];
                    double sc = scal[i];
                    double out;

                    ///////////////////
                    // Tasklet code (four)
                    out = (((ione + (itwo[0] * itwo[1])) + ithree) + sc);
                    ///////////////////

                    B[i] = out;
                }
            }
            auto __dace_tend_0_0_23 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_0_23 = __dace_tend_0_0_23 - __dace_tbegin_0_0_23;
            dace::perf::report.add("timer_Map outer_fission", __dace_tdiff_0_0_23.count());
        }
        delete[] s2;
        delete[] s3out;
        delete[] s1;
        delete[] scal;
    }
    dace::perf::report.save(".dacecache/mapfission/perf");
}

DACE_EXPORTED void __program_mapfission(double * __restrict__ A, double * __restrict__ B)
{
    __program_mapfission_internal(A, B);
}

DACE_EXPORTED int __dace_init_mapfission(double * __restrict__ A, double * __restrict__ B)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_mapfission(double * __restrict__ A, double * __restrict__ B)
{
}

