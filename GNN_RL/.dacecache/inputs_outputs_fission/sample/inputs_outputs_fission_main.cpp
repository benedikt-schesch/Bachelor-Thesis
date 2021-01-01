#include <stdlib.h>
#include "inputs_outputs_fission.h"

int main(int argc, char** argv) {
  double * __restrict__ in1 = (double*) calloc(2, sizeof(double));
  double * __restrict__ in2 = (double*) calloc(2, sizeof(double));
  double * __restrict__ out1 = (double*) calloc(2, sizeof(double));
  double * __restrict__ out2 = (double*) calloc(2, sizeof(double));

  __dace_init_inputs_outputs_fission(in1, in2, out1, out2);
  __program_inputs_outputs_fission(in1, in2, out1, out2);
  __dace_exit_inputs_outputs_fission(in1, in2, out1, out2);

  free(in1);
  free(in2);
  free(out1);
  free(out2);
  return 0;
}
