#include <stdlib.h>
#include "multiple_cr.h"

int main(int argc, char** argv) {
  int N = 42;
  long long * __restrict__ A = (long long*) calloc(N, sizeof(long long));
  long long * __restrict__ p = (long long*) calloc(1, sizeof(long long));
  long long * __restrict__ s = (long long*) calloc(1, sizeof(long long));

  __dace_init_multiple_cr(A, p, s, N);
  __program_multiple_cr(A, p, s, N);
  __dace_exit_multiple_cr(A, p, s, N);

  free(A);
  free(p);
  free(s);
  return 0;
}
