#include <stdlib.h>
#include "uaddtest.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(25, sizeof(long long));
  long long * __restrict__ B = (long long*) calloc(25, sizeof(long long));

  __dace_init_uaddtest(A, B);
  __program_uaddtest(A, B);
  __dace_exit_uaddtest(A, B);

  free(A);
  free(B);
  return 0;
}
