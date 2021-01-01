#include <stdlib.h>
#include "nested_stream_test.h"

int main(int argc, char** argv) {
  int * __restrict__ B = (int*) calloc(2, sizeof(int));

  __dace_init_nested_stream_test(B);
  __program_nested_stream_test(B);
  __dace_exit_nested_stream_test(B);

  free(B);
  return 0;
}
