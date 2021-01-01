#include <stdlib.h>
#include "tovec.h"

int main(int argc, char** argv) {
  dace::vec<double, 2> * __restrict__ A = (dace::vec<double, 2>*) calloc(10, sizeof(dace::vec<double, 2>));
  dace::vec<double, 2> * __restrict__ __return = (dace::vec<double, 2>*) calloc(10, sizeof(dace::vec<double, 2>));

  __dace_init_tovec(A, __return);
  __program_tovec(A, __return);
  __dace_exit_tovec(A, __return);

  free(A);
  free(__return);
  return 0;
}
