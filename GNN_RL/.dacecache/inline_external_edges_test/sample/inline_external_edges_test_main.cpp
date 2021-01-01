#include <stdlib.h>
#include "inline_external_edges_test.h"

int main(int argc, char** argv) {
  float * __restrict__ L = (float*) calloc(2, sizeof(float));
  float * __restrict__ M = (float*) calloc(2, sizeof(float));

  __dace_init_inline_external_edges_test(L, M);
  __program_inline_external_edges_test(L, M);
  __dace_exit_inline_external_edges_test(L, M);

  free(L);
  free(M);
  return 0;
}
