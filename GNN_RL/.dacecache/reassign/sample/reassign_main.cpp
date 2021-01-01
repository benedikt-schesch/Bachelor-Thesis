#include <stdlib.h>
#include "reassign.h"

int main(int argc, char** argv) {
  double * __restrict__ a = (double*) calloc(1, sizeof(double));

  __dace_init_reassign(a);
  __program_reassign(a);
  __dace_exit_reassign(a);

  free(a);
  return 0;
}
