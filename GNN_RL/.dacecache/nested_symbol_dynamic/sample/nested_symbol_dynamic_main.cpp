#include <stdlib.h>
#include "nested_symbol_dynamic.h"

int main(int argc, char** argv) {
  int N = 42;
  double * __restrict__ A = (double*) calloc(N, sizeof(double));

  __dace_init_nested_symbol_dynamic(A, N);
  __program_nested_symbol_dynamic(A, N);
  __dace_exit_nested_symbol_dynamic(A, N);

  free(A);
  return 0;
}
