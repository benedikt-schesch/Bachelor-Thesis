#include <stdlib.h>
#include "returnpi.h"

int main(int argc, char** argv) {
  double * __restrict__ result = (double*) calloc(20, sizeof(double));

  __dace_init_returnpi(result);
  __program_returnpi(result);
  __dace_exit_returnpi(result);

  free(result);
  return 0;
}
