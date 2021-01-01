#include <stdlib.h>
#include "augmulttest.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(25, sizeof(long long));
  long long * __restrict__ B = (long long*) calloc(25, sizeof(long long));

  __dace_init_augmulttest(A, B);
  __program_augmulttest(A, B);
  __dace_exit_augmulttest(A, B);

  free(A);
  free(B);
  return 0;
}
