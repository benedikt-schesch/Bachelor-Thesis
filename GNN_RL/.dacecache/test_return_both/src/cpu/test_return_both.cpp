/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

struct _val_and_idx {
    int idx;
    double val;
};
void __program_test_return_both_internal(double * __restrict__ IN, int * __restrict__ __tmp1, double * __restrict__ __tmp2)
{
    _val_and_idx *__tmp0 = new _val_and_idx DACE_ALIGN(64)[30];

    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 10; __i0 += 1) {
                for (auto __i2 = 0; __i2 < 3; __i2 += 1) {
                    {
                        _val_and_idx __init;

                        ///////////////////
                        // Tasklet code (_argmin_convert_)
                        __init = _val_and_idx { .idx = (- 1), .val = 1.7976931348623157e+308 };
                        ///////////////////

                        __tmp0[((3 * __i0) + __i2)] = __init;
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 10; __i0 += 1) {
                for (auto __i1 = 0; __i1 < 5; __i1 += 1) {
                    for (auto __i2 = 0; __i2 < 3; __i2 += 1) {
                        {
                            double __in = IN[(((15 * __i0) + (3 * __i1)) + __i2)];
                            _val_and_idx __out;

                            ///////////////////
                            // Tasklet code (_argmin_reduce_)
                            __out = _val_and_idx { .idx = __i1, .val = __in };
                            ///////////////////

                            dace::wcr_custom<_val_and_idx>:: template reduce_atomic([] (const _val_and_idx& x, const _val_and_idx& y) { return _val_and_idx { .idx = ((x.val > y.val) ? y.idx : x.idx), .val = min(x.val, y.val) }; }, __tmp0 + ((3 * __i0) + __i2), __out);
                        }
                    }
                }
            }
        }
    }
    {
        
        
        {
            #pragma omp parallel for
            for (auto __i0 = 0; __i0 < 10; __i0 += 1) {
                for (auto __i2 = 0; __i2 < 3; __i2 += 1) {
                    {
                        _val_and_idx __in = __tmp0[((3 * __i0) + __i2)];
                        int __out_idx;
                        double __out_val;

                        ///////////////////
                        // Tasklet code (_argmin_extract_)
                        __out_val = __in.val;
                        __out_idx = __in.idx;
                        ///////////////////

                        __tmp1[((3 * __i0) + __i2)] = __out_idx;
                        __tmp2[((3 * __i0) + __i2)] = __out_val;
                    }
                }
            }
        }
    }
    delete[] __tmp0;
}

DACE_EXPORTED void __program_test_return_both(double * __restrict__ IN, int * __restrict__ __tmp1, double * __restrict__ __tmp2)
{
    __program_test_return_both_internal(IN, __tmp1, __tmp2);
}

DACE_EXPORTED int __dace_init_test_return_both(double * __restrict__ IN, int * __restrict__ __tmp1, double * __restrict__ __tmp2)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_test_return_both(double * __restrict__ IN, int * __restrict__ __tmp1, double * __restrict__ __tmp2)
{
}

