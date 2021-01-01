#include <stdlib.h>
#include "augaddtest.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(25, sizeof(long long));
  long long * __restrict__ B = (long long*) calloc(25, sizeof(long long));

  __dace_init_augaddtest(A, B);
  __program_augaddtest(A, B);
  __dace_exit_augaddtest(A, B);

  free(A);
  free(B);
  return 0;
}
