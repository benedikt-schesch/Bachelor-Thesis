#include <stdlib.h>
#include "tile_twice_test.h"

int main(int argc, char** argv) {
  double * __restrict__ a = (double*) calloc(200, sizeof(double));

  __dace_init_tile_twice_test(a);
  __program_tile_twice_test(a);
  __dace_exit_tile_twice_test(a);

  free(a);
  return 0;
}
