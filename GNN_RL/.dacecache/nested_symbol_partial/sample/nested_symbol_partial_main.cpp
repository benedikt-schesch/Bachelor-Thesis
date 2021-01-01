#include <stdlib.h>
#include "nested_symbol_partial.h"

int main(int argc, char** argv) {
  int sym_0 = 42;
  double * __restrict__ A = (double*) calloc(1, sizeof(double));

  __dace_init_nested_symbol_partial(A, sym_0);
  __program_nested_symbol_partial(A, sym_0);
  __dace_exit_nested_symbol_partial(A, sym_0);

  free(A);
  return 0;
}
