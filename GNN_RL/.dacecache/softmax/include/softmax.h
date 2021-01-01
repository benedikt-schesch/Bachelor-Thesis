extern "C" int __dace_init_softmax(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN);
extern "C" int __dace_exit_softmax(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN);
extern "C" void __program_softmax(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN);
