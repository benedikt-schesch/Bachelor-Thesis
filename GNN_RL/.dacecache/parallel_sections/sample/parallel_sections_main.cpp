#include <stdlib.h>
#include "parallel_sections.h"

int main(int argc, char** argv) {
  int N = 42;
  int * __restrict__ array_in = (int*) calloc((2 * N), sizeof(int));
  int * __restrict__ array_out = (int*) calloc(N, sizeof(int));

  __dace_init_parallel_sections(array_in, array_out, N);
  __program_parallel_sections(array_in, array_out, N);
  __dace_exit_parallel_sections(array_in, array_out, N);

  free(array_in);
  free(array_out);
  return 0;
}
