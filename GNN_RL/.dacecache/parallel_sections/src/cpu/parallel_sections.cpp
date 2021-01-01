/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>


#include <chrono>
namespace dace { namespace perf { Report report; } }
#include <chrono>
void __program_parallel_sections_internal(int * __restrict__ array_in, int * __restrict__ array_out, int N)
{
    dace::perf::report.reset();

    {
        dace::Stream<int> fifo_in_a(1);
        dace::Stream<int> fifo_in_b(1);
        dace::Stream<int> fifo_out(1);
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                {
                    auto __dace_tbegin_0_0_8 = std::chrono::high_resolution_clock::now();
                    for (auto i = 0; i < N; i += 1) {
                        {
                            int from_memory = array_in[i];

                            ///////////////////
                            // Tasklet code (read_a)
                            fifo_in_a.push(from_memory);
                            ///////////////////

                        }
                    }
                    auto __dace_tend_0_0_8 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_8 = __dace_tend_0_0_8 - __dace_tbegin_0_0_8;
                    dace::perf::report.add("timer_Map read_map_a", __dace_tdiff_0_0_8.count());
                }
            } // End omp section
            #pragma omp section
            {
                {
                    auto __dace_tbegin_0_0_11 = std::chrono::high_resolution_clock::now();
                    for (auto i = N; i < (2 * N); i += 1) {
                        {
                            int from_memory = array_in[i];

                            ///////////////////
                            // Tasklet code (read_b)
                            fifo_in_b.push(from_memory);
                            ///////////////////

                        }
                    }
                    auto __dace_tend_0_0_11 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_11 = __dace_tend_0_0_11 - __dace_tbegin_0_0_11;
                    dace::perf::report.add("timer_Map read_map_b", __dace_tdiff_0_0_11.count());
                }
            } // End omp section
            #pragma omp section
            {
                {
                    auto __dace_tbegin_0_0_14 = std::chrono::high_resolution_clock::now();
                    for (auto i = 0; i < N; i += 1) {
                        {
                            int a = (fifo_in_a).pop();
                            int b = (fifo_in_b).pop();

                            ///////////////////
                            // Tasklet code (compute)
                            fifo_out.push((a + b));
                            ///////////////////

                        }
                    }
                    auto __dace_tend_0_0_14 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_14 = __dace_tend_0_0_14 - __dace_tbegin_0_0_14;
                    dace::perf::report.add("timer_Map compute_map", __dace_tdiff_0_0_14.count());
                }
            } // End omp section
            #pragma omp section
            {
                {
                    auto __dace_tbegin_0_0_17 = std::chrono::high_resolution_clock::now();
                    for (auto i = 0; i < N; i += 1) {
                        {
                            int from_stream = (fifo_out).pop();
                            int to_memory;

                            ///////////////////
                            // Tasklet code (write)
                            to_memory = from_stream;
                            ///////////////////

                            array_out[i] = to_memory;
                        }
                    }
                    auto __dace_tend_0_0_17 = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double, std::milli> __dace_tdiff_0_0_17 = __dace_tend_0_0_17 - __dace_tbegin_0_0_17;
                    dace::perf::report.add("timer_Map write_map", __dace_tdiff_0_0_17.count());
                }
            } // End omp section
        } // End omp sections
    }
    dace::perf::report.save(".dacecache/parallel_sections/perf");
}

DACE_EXPORTED void __program_parallel_sections(int * __restrict__ array_in, int * __restrict__ array_out, int N)
{
    __program_parallel_sections_internal(array_in, array_out, N);
}

DACE_EXPORTED int __dace_init_parallel_sections(int * __restrict__ array_in, int * __restrict__ array_out, int N)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_parallel_sections(int * __restrict__ array_in, int * __restrict__ array_out, int N)
{
}

