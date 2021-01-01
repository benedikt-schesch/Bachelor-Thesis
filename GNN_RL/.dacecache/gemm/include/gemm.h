extern "C" int __dace_init_gemm(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float alpha, float beta);
extern "C" int __dace_exit_gemm(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float alpha, float beta);
extern "C" void __program_gemm(float * __restrict__ A, float * __restrict__ B, float * __restrict__ C, float alpha, float beta);
