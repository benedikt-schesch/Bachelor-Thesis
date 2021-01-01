
#include <cuda_runtime.h>
#include <dace/dace.h>



DACE_EXPORTED int __dace_init_cuda(float * __restrict__ A, float * __restrict__ B, float * __restrict__ Y);
DACE_EXPORTED void __dace_exit_cuda(float * __restrict__ A, float * __restrict__ B, float * __restrict__ Y);



namespace dace { namespace cuda {
    cudaStream_t __streams[2];
    cudaEvent_t __events[2];
    int num_streams = 2;
    int num_events = 2;
} }

int __dace_init_cuda(float * __restrict__ A, float * __restrict__ B, float * __restrict__ Y) {
    int count;

    // Check that we are able to run cuda code
    if (cudaGetDeviceCount(&count) != cudaSuccess)
    {
        printf("ERROR: GPU drivers are not configured or cuda-capable device "
               "not found\n");
        return 1;
    }
    if (count == 0)
    {
        printf("ERROR: No cuda-capable devices found\n");
        return 2;
    }

    // Initialize cuda before we run the application
    float *dev_X;
    cudaMalloc((void **) &dev_X, 1);
    cudaFree(dev_X);

    // Create cuda streams and events
    for(int i = 0; i < 2; ++i) {
        cudaStreamCreateWithFlags(&dace::cuda::__streams[i], cudaStreamNonBlocking);
    }
    for(int i = 0; i < 2; ++i) {
        cudaEventCreateWithFlags(&dace::cuda::__events[i], cudaEventDisableTiming);
    }

    

    return 0;
}

void __dace_exit_cuda(float * __restrict__ A, float * __restrict__ B, float * __restrict__ Y) {
    

    // Destroy cuda streams and events
    for(int i = 0; i < 2; ++i) {
        cudaStreamDestroy(dace::cuda::__streams[i]);
    }
    for(int i = 0; i < 2; ++i) {
        cudaEventDestroy(dace::cuda::__events[i]);
    }
}


