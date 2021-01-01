/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_sftw_internal(double * __restrict__ A)
{
    dace::perf::report.reset();
    double *dup = new double DACE_ALIGN(64)[20];
    double *D = new double DACE_ALIGN(64)[20];
    double *C = new double DACE_ALIGN(64)[20];

    {
        double *B = new double DACE_ALIGN(64)[20];
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    auto __dace_tbegin_0_0_0 = std::chrono::high_resolution_clock::now();
                    #pragma omp parallel for
                    for (auto i = 0; i < 20; i += 1) {
                        {
                            double a = A[i];
                            double b;

                            ///////////////////
                            // Tasklet code (sftw_15)
                            b = a;
                            ///////////////////

                            B[i] = b;
                        }
                    }
                    auto __dace_tend_0_0_0 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_0 = __dace_tend_0_0_0 - __dace_tbegin_0_0_0;
                    dace::perf::report.add("timer_Map sftw_14", __dace_tdiff_0_0_0.count());
                }
                {
                    auto __dace_tbegin_0_0_4 = std::chrono::high_resolution_clock::now();
                    #pragma omp parallel for
                    for (auto i = 0; i < 20; i += 1) {
                        {
                            double a = B[i];
                            double b;

                            ///////////////////
                            // Tasklet code (sftw_21)
                            b = a;
                            ///////////////////

                            dup[i] = b;
                        }
                    }
                    auto __dace_tend_0_0_4 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_4 = __dace_tend_0_0_4 - __dace_tbegin_0_0_4;
                    dace::perf::report.add("timer_Map sftw_20", __dace_tdiff_0_0_4.count());
                }
                {
                    auto __dace_tbegin_0_0_7 = std::chrono::high_resolution_clock::now();
                    #pragma omp parallel for
                    for (auto i = 0; i < 20; i += 1) {
                        {
                            double a = dup[i];
                            double b;

                            ///////////////////
                            // Tasklet code (sftw_27)
                            b = (a + 2);
                            ///////////////////

                            D[i] = b;
                        }
                    }
                    auto __dace_tend_0_0_7 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_7 = __dace_tend_0_0_7 - __dace_tbegin_0_0_7;
                    dace::perf::report.add("timer_Map sftw_26", __dace_tdiff_0_0_7.count());
                }
            } // End omp section
            #pragma omp section
            {
                {
                    auto __dace_tbegin_0_0_10 = std::chrono::high_resolution_clock::now();
                    #pragma omp parallel for
                    for (auto i = 0; i < 20; i += 1) {
                        {
                            double a = A[i];
                            double b;

                            ///////////////////
                            // Tasklet code (sftw_33)
                            b = (a + 1);
                            ///////////////////

                            C[i] = b;
                        }
                    }
                    auto __dace_tend_0_0_10 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_10 = __dace_tend_0_0_10 - __dace_tbegin_0_0_10;
                    dace::perf::report.add("timer_Map sftw_32", __dace_tdiff_0_0_10.count());
                }
            } // End omp section
        } // End omp sections
        delete[] B;
    }
    {
        double *E = new double DACE_ALIGN(64)[20];
        
        
        {
            auto __dace_tbegin_0_1_0 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                {
                    double a = C[i];
                    double b;

                    ///////////////////
                    // Tasklet code (sftw_39)
                    b = (a + 1);
                    ///////////////////

                    dup[i] = b;
                }
            }
            auto __dace_tend_0_1_0 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_1_0 = __dace_tend_0_1_0 - __dace_tbegin_0_1_0;
            dace::perf::report.add("timer_Map sftw_38", __dace_tdiff_0_1_0.count());
        }
        {
            auto __dace_tbegin_0_1_4 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                {
                    double a = dup[i];
                    double b;

                    ///////////////////
                    // Tasklet code (sftw_45)
                    b = (a + 3);
                    ///////////////////

                    E[i] = b;
                }
            }
            auto __dace_tend_0_1_4 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_1_4 = __dace_tend_0_1_4 - __dace_tbegin_0_1_4;
            dace::perf::report.add("timer_Map sftw_44", __dace_tdiff_0_1_4.count());
        }
        {
            auto __dace_tbegin_0_1_7 = std::chrono::high_resolution_clock::now();
            #pragma omp parallel for
            for (auto i = 0; i < 20; i += 1) {
                {
                    double d = D[i];
                    double e = E[i];
                    double a;

                    ///////////////////
                    // Tasklet code (sftw_51)
                    a = (d + e);
                    ///////////////////

                    A[i] = a;
                }
            }
            auto __dace_tend_0_1_7 = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> __dace_tdiff_0_1_7 = __dace_tend_0_1_7 - __dace_tbegin_0_1_7;
            dace::perf::report.add("timer_Map sftw_50", __dace_tdiff_0_1_7.count());
        }
        delete[] E;
    }
    delete[] dup;
    delete[] D;
    delete[] C;
    dace::perf::report.save(".dacecache/sftw/perf");
}

DACE_EXPORTED void __program_sftw(double * __restrict__ A)
{
    __program_sftw_internal(A);
}

DACE_EXPORTED int __dace_init_sftw(double * __restrict__ A)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_sftw(double * __restrict__ A)
{
}

