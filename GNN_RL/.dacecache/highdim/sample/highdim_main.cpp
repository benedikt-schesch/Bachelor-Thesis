#include <stdlib.h>
#include "highdim.h"

int main(int argc, char** argv) {
  int K = 42;
  int L = 42;
  int M = 42;
  int N = 42;
  int U = 42;
  int W = 42;
  int X = 42;
  int Y = 42;
  int Z = 42;
  unsigned long long * __restrict__ A = (unsigned long long*) calloc(((((((((K * L) * M) * N) * U) * W) * X) * Y) * Z), sizeof(unsigned long long));
  unsigned long long * __restrict__ B = (unsigned long long*) calloc((((K * L) * M) * N), sizeof(unsigned long long));

  __dace_init_highdim(A, B, K, L, M, N, U, W, X, Y, Z);
  __program_highdim(A, B, K, L, M, N, U, W, X, Y, Z);
  __dace_exit_highdim(A, B, K, L, M, N, U, W, X, Y, Z);

  free(A);
  free(B);
  return 0;
}
