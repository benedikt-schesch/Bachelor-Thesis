#include <stdlib.h>
#include "program.h"

int main(int argc, char** argv) {
  double * __restrict__ input = (double*) calloc(20, sizeof(double));
  double * __restrict__ output = (double*) calloc(20, sizeof(double));

  __dace_init_program(input, output);
  __program_program(input, output);
  __dace_exit_program(input, output);

  free(input);
  free(output);
  return 0;
}
