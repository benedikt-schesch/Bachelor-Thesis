#include <stdlib.h>
#include "argmax.h"

int main(int argc, char** argv) {
  pair * __restrict__ __return = (pair*) calloc(1, sizeof(pair));
  double * __restrict__ x = (double*) calloc(1024, sizeof(double));

  __dace_init_argmax(__return, x);
  __program_argmax(__return, x);
  __dace_exit_argmax(__return, x);

  free(__return);
  free(x);
  return 0;
}
