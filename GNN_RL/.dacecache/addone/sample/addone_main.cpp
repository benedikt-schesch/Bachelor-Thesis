#include <stdlib.h>
#include "addone.h"

int main(int argc, char** argv) {
  csr * __restrict__ sparsemats_in = (csr*) calloc(5, sizeof(csr));
  csr * __restrict__ sparsemats_out = (csr*) calloc(5, sizeof(csr));

  __dace_init_addone(sparsemats_in, sparsemats_out);
  __program_addone(sparsemats_in, sparsemats_out);
  __dace_exit_addone(sparsemats_in, sparsemats_out);

  free(sparsemats_in);
  free(sparsemats_out);
  return 0;
}
