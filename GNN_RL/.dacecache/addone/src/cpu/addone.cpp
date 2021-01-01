/* DaCe AUTO-GENERATED FILE. DO NOT MODIFY */
#include <dace/dace.h>

struct csr {
    int* colind;
    int cols;
    float* data;
    int nnz;
    int* rowptr;
    int rows;
    int rowsp1;
};
void __program_addone_internal(csr * __restrict__ sparsemats_in, csr * __restrict__ sparsemats_out)
{

    {
        
        
        {
            #pragma omp parallel for
            for (auto i = 0; i < 5; i += 1) {
                {
                    csr mat_in = sparsemats_in[i];
                    csr* mat_out = sparsemats_out + i;

                    ///////////////////

                    for (int j = 0; j < mat_in.nnz; ++j) {
                        mat_out->data[j] = mat_in.data[j] + 1.0f;
                    }
                    ///////////////////

                }
            }
        }
    }
}

DACE_EXPORTED void __program_addone(csr * __restrict__ sparsemats_in, csr * __restrict__ sparsemats_out)
{
    __program_addone_internal(sparsemats_in, sparsemats_out);
}

DACE_EXPORTED int __dace_init_addone(csr * __restrict__ sparsemats_in, csr * __restrict__ sparsemats_out)
{
    int __result = 0;

    return __result;
}

DACE_EXPORTED void __dace_exit_addone(csr * __restrict__ sparsemats_in, csr * __restrict__ sparsemats_out)
{
}

