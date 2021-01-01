#include <stdlib.h>
#include "cwsTFT.h"

int main(int argc, char** argv) {
  int W = 42;
  int X = 42;
  int Y = 42;
  int Z = 42;
  double * __restrict__ A = (double*) calloc(120, sizeof(double));
  double * __restrict__ B = (double*) calloc(120, sizeof(double));

  __dace_init_cwsTFT(A, B, W, X, Y, Z);
  __program_cwsTFT(A, B, W, X, Y, Z);
  __dace_exit_cwsTFT(A, B, W, X, Y, Z);

  free(A);
  free(B);
  return 0;
}
