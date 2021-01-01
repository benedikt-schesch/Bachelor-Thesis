#include <stdlib.h>
#include "usubtest.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(25, sizeof(long long));
  long long * __restrict__ B = (long long*) calloc(25, sizeof(long long));

  __dace_init_usubtest(A, B);
  __program_usubtest(A, B);
  __dace_exit_usubtest(A, B);

  free(A);
  free(B);
  return 0;
}
