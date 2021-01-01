#include <stdlib.h>
#include "mapfission_offsets2.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(20, sizeof(double));

  __dace_init_mapfission_offsets2(A);
  __program_mapfission_offsets2(A);
  __dace_exit_mapfission_offsets2(A);

  free(A);
  return 0;
}
