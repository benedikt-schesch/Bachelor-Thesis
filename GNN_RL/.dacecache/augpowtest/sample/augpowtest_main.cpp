#include <stdlib.h>
#include "augpowtest.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(25, sizeof(long long));
  long long * __restrict__ B = (long long*) calloc(25, sizeof(long long));

  __dace_init_augpowtest(A, B);
  __program_augpowtest(A, B);
  __dace_exit_augpowtest(A, B);

  free(A);
  free(B);
  return 0;
}
