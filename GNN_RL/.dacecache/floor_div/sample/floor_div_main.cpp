#include <stdlib.h>
#include "floor_div.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ Input = (double*) calloc(N, sizeof(double));
  double * __restrict__ Output = (double*) calloc(N, sizeof(double));

  __dace_init_floor_div(Input, Output, N);
  __program_floor_div(Input, Output, N);
  __dace_exit_floor_div(Input, Output, N);

  free(Input);
  free(Output);
  return 0;
}
