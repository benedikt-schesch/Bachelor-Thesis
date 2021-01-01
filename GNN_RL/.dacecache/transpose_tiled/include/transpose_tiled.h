extern "C" int __dace_init_transpose_tiled(float * __restrict__ A, float * __restrict__ B, int H, int TH, int TW, int W);
extern "C" int __dace_exit_transpose_tiled(float * __restrict__ A, float * __restrict__ B, int H, int TH, int TW, int W);
extern "C" void __program_transpose_tiled(float * __restrict__ A, float * __restrict__ B, int H, int TH, int TW, int W);
