#include <stdlib.h>
#include "nest_subgraph.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(1, sizeof(double));
  double * __restrict__ B = (double*) calloc(1, sizeof(double));

  __dace_init_nest_subgraph(A, B);
  __program_nest_subgraph(A, B);
  __dace_exit_nest_subgraph(A, B);

  free(A);
  free(B);
  return 0;
}
