extern "C" int __dace_init_callback_with_arrays(double * __restrict__ in_arr, double * __restrict__ out_arr, void (*arrfunc)(double const *,double const *), int sym_0, int sym_1, int sym_2);
extern "C" int __dace_exit_callback_with_arrays(double * __restrict__ in_arr, double * __restrict__ out_arr, void (*arrfunc)(double const *,double const *), int sym_0, int sym_1, int sym_2);
extern "C" void __program_callback_with_arrays(double * __restrict__ in_arr, double * __restrict__ out_arr, void (*arrfunc)(double const *,double const *), int sym_0, int sym_1, int sym_2);
