#include <stdlib.h>
#include "sftw.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(20, sizeof(double));

  __dace_init_sftw(A);
  __program_sftw(A);
  __dace_exit_sftw(A);

  free(A);
  return 0;
}
