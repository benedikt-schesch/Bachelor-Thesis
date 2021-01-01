#include <stdlib.h>
#include "cudahello.h"

int main(int argc, char** argv) {
  int H = 42;
  int W = 42;
  double * __restrict__ V = (double*) calloc((H * W), sizeof(double));
  double * __restrict__ Vout = (double*) calloc((H * W), sizeof(double));

  __dace_init_cudahello(V, Vout, H, W);
  __program_cudahello(V, Vout, H, W);
  __dace_exit_cudahello(V, Vout, H, W);

  free(V);
  free(Vout);
  return 0;
}
