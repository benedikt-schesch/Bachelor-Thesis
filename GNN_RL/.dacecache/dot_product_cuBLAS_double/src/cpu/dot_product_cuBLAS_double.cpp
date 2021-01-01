/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>
#include "../include/dace_cublas.h"

void __program_dot_product_cuBLAS_double_internal(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    double * x_device = nullptr;
    cudaMalloc(&x_device, n * sizeof(double));
    double * y_device = nullptr;
    cudaMalloc(&y_device, n * sizeof(double));
    double * result_device = nullptr;
    cudaMalloc(&result_device, 1 * sizeof(double));

    {
        
        
        #pragma omp parallel sections
        {
            #pragma omp section
            {
                cudaMemcpyAsync(x_device, x, n * sizeof(double), cudaMemcpyHostToDevice, dace::cuda::__streams[0]);
            } // End omp section
            #pragma omp section
            {
                cudaMemcpyAsync(y_device, y, n * sizeof(double), cudaMemcpyHostToDevice, dace::cuda::__streams[1]);
            } // End omp section
        } // End omp sections
        cudaStreamSynchronize(dace::cuda::__streams[0]);
        cudaStreamSynchronize(dace::cuda::__streams[1]);
        
        
    }
    {
        
        
        {
            double * _x = &x_device[0];
            double * _y = &y_device[0];
            double* _result = result_device;

            ///////////////////
            int __dace_current_stream_id = 0;
            cudaStream_t __dace_current_stream = dace::cuda::__streams[__dace_current_stream_id];
            const int __dace_cuda_device = 0;
            auto &__dace_cublas_handle = dace::blas::CublasHandle::Get(__dace_cuda_device);
            cublasSetStream(__dace_cublas_handle, __dace_current_stream);
            cublasDdot(__dace_cublas_handle, n, ___x.ptr<1>(), 1, ___y.ptr<1>(), 1, ___result.ptr<1>());
            ///////////////////

        }
        cudaStreamSynchronize(dace::cuda::__streams[0]);
        
        
    }
    {
        
        
        cudaMemcpyAsync(result, result_device, 1 * sizeof(double), cudaMemcpyDeviceToHost, dace::cuda::__streams[0]);
        cudaStreamSynchronize(dace::cuda::__streams[0]);
        
        
    }
    cudaFree(x_device);
    cudaFree(y_device);
    cudaFree(result_device);
}

DACE_EXPORTED void __program_dot_product_cuBLAS_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    __program_dot_product_cuBLAS_double_internal(result, x, y, n);
}
DACE_EXPORTED int __dace_init_cuda(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n);
DACE_EXPORTED int __dace_exit_cuda(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n);

DACE_EXPORTED int __dace_init_dot_product_cuBLAS_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    int __result = 0;
    __result |= __dace_init_cuda(result, x, y, n);

    return __result;
}

DACE_EXPORTED void __dace_exit_dot_product_cuBLAS_double(double * __restrict__ result, double * __restrict__ x, double * __restrict__ y, int n)
{
    __dace_exit_cuda(result, x, y, n);
}

