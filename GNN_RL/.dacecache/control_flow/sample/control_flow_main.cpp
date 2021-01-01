#include <stdlib.h>
#include "control_flow.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(10, sizeof(double));

  __dace_init_control_flow(A);
  __program_control_flow(A);
  __dace_exit_control_flow(A);

  free(A);
  return 0;
}
