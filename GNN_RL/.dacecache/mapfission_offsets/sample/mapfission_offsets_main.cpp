#include <stdlib.h>
#include "mapfission_offsets.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(20, sizeof(double));

  __dace_init_mapfission_offsets(A);
  __program_mapfission_offsets(A);
  __dace_exit_mapfission_offsets(A);

  free(A);
  return 0;
}
