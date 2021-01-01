#include <stdlib.h>
#include "mysdfg.h"

int main(int argc, char** argv) {
  int N = 42;
  int * __restrict__ A = (int*) calloc(N, sizeof(int));
  int * __restrict__ B = (int*) calloc(N, sizeof(int));

  __dace_init_mysdfg(A, B, N);
  __program_mysdfg(A, B, N);
  __dace_exit_mysdfg(A, B, N);

  free(A);
  free(B);
  return 0;
}
