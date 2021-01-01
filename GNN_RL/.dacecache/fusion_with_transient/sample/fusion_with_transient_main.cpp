#include <stdlib.h>
#include "fusion_with_transient.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(40, sizeof(double));

  __dace_init_fusion_with_transient(A);
  __program_fusion_with_transient(A);
  __dace_exit_fusion_with_transient(A);

  free(A);
  return 0;
}
