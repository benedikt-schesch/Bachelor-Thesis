#include <stdlib.h>
#include "tlarray.h"

int main(int argc, char** argv) {
  int * __restrict__ A = (int*) calloc(128, sizeof(int));

  __dace_init_tlarray(A);
  __program_tlarray(A);
  __dace_exit_tlarray(A);

  free(A);
  return 0;
}
