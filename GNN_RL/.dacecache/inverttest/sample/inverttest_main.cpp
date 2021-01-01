#include <stdlib.h>
#include "inverttest.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(25, sizeof(long long));
  long long * __restrict__ B = (long long*) calloc(25, sizeof(long long));

  __dace_init_inverttest(A, B);
  __program_inverttest(A, B);
  __dace_exit_inverttest(A, B);

  free(A);
  free(B);
  return 0;
}
