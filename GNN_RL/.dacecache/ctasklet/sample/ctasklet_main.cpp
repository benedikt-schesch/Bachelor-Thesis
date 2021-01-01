#include <stdlib.h>
#include "ctasklet.h"

int main(int argc, char** argv) {
  int N = 42;
  int * __restrict__ A = (int*) calloc(N, sizeof(int));
  int * __restrict__ B = (int*) calloc(N, sizeof(int));

  __dace_init_ctasklet(A, B, N);
  __program_ctasklet(A, B, N);
  __dace_exit_ctasklet(A, B, N);

  free(A);
  free(B);
  return 0;
}
