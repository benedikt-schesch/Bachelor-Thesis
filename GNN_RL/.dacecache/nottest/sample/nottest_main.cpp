#include <stdlib.h>
#include "nottest.h"

int main(int argc, char** argv) {
  bool * __restrict__ A = (bool*) calloc(25, sizeof(bool));
  bool * __restrict__ B = (bool*) calloc(25, sizeof(bool));

  __dace_init_nottest(A, B);
  __program_nottest(A, B);
  __dace_exit_nottest(A, B);

  free(A);
  free(B);
  return 0;
}
