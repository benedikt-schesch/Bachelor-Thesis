#include <stdlib.h>
#include "augrshifttest.h"

int main(int argc, char** argv) {
  long long * __restrict__ A = (long long*) calloc(25, sizeof(long long));
  long long * __restrict__ B = (long long*) calloc(25, sizeof(long long));

  __dace_init_augrshifttest(A, B);
  __program_augrshifttest(A, B);
  __dace_exit_augrshifttest(A, B);

  free(A);
  free(B);
  return 0;
}
