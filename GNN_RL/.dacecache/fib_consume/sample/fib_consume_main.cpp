#include <stdlib.h>
#include "fib_consume.h"

int main(int argc, char** argv) {
  int * __restrict__ iv = (int*) calloc(1, sizeof(int));
  float * __restrict__ res = (float*) calloc(1, sizeof(float));

  __dace_init_fib_consume(iv, res);
  __program_fib_consume(iv, res);
  __dace_exit_fib_consume(iv, res);

  free(iv);
  free(res);
  return 0;
}
