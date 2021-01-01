#include <stdlib.h>
#include "inline_noinput.h"

int main(int argc, char** argv) {
  double * __restrict__ A = (double*) calloc(2, sizeof(double));

  __dace_init_inline_noinput(A);
  __program_inline_noinput(A);
  __dace_exit_inline_noinput(A);

  free(A);
  return 0;
}
