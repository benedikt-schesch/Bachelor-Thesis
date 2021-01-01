#include <stdlib.h>
#include "vecAdd_graph.h"

int main(int argc, char** argv) {
  int n = 42;
  dace::vec<float, 4> * __restrict__ _res = (dace::vec<float, 4>*) calloc((n / 4), sizeof(dace::vec<float, 4>));
  dace::vec<float, 4> * __restrict__ _x = (dace::vec<float, 4>*) calloc((n / 4), sizeof(dace::vec<float, 4>));
  dace::vec<float, 4> * __restrict__ _y = (dace::vec<float, 4>*) calloc((n / 4), sizeof(dace::vec<float, 4>));

  __dace_init_vecAdd_graph(_res, _x, _y, n);
  __program_vecAdd_graph(_res, _x, _y, n);
  __dace_exit_vecAdd_graph(_res, _x, _y, n);

  free(_res);
  free(_x);
  free(_y);
  return 0;
}
