#include <stdlib.h>
#include "whiletest.h"

int main(int argc, char** argv) {
  int * __restrict__ A = (int*) calloc(1, sizeof(int));

  __dace_init_whiletest(A);
  __program_whiletest(A);
  __dace_exit_whiletest(A);

  free(A);
  return 0;
}
