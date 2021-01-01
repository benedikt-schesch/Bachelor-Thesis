#include <stdlib.h>
#include "cpp_tasklet.h"

int main(int argc, char** argv) {
  unsigned int * __restrict__ A = (unsigned int*) calloc(2, sizeof(unsigned int));
  unsigned int * __restrict__ B = (unsigned int*) calloc(1, sizeof(unsigned int));

  __dace_init_cpp_tasklet(A, B);
  __program_cpp_tasklet(A, B);
  __dace_exit_cpp_tasklet(A, B);

  free(A);
  free(B);
  return 0;
}
