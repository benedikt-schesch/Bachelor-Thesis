#include <stdlib.h>
#include "fusion_chain.h"

int main(int argc, char** argv) {
  float * __restrict__ A = (float*) calloc(200, sizeof(float));
  float * __restrict__ B = (float*) calloc(200, sizeof(float));

  __dace_init_fusion_chain(A, B);
  __program_fusion_chain(A, B);
  __dace_exit_fusion_chain(A, B);

  free(A);
  free(B);
  return 0;
}
