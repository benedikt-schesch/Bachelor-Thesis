#include <stdlib.h>
#include "nsstest.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(2, sizeof(double));

  __dace_init_nsstest(A);
  __program_nsstest(A);
  __dace_exit_nsstest(A);

  free(A);
  return 0;
}
