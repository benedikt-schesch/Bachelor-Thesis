extern "C" int __dace_init_softmax_fused(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN);
extern "C" int __dace_exit_softmax_fused(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN);
extern "C" void __program_softmax_fused(float * __restrict__ X_in, float * __restrict__ __return, int B, int H, int SM, int SN);
