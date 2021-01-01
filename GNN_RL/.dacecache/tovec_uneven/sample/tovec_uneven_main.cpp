#include <stdlib.h>
#include "tovec_uneven.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ A = (double*) calloc((N + 2), sizeof(double));

  __dace_init_tovec_uneven(A, N);
  __program_tovec_uneven(A, N);
  __dace_exit_tovec_uneven(A, N);

  free(A);
  return 0;
}
