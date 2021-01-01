#include <stdlib.h>
#include "inline_chain_test.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(400, sizeof(double));

  __dace_init_inline_chain_test(A);
  __program_inline_chain_test(A);
  __dace_exit_inline_chain_test(A);

  free(A);
  return 0;
}
