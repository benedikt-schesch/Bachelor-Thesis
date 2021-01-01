#include <stdlib.h>
#include "toplevel_interstate_test.h"

int main(int argc, char** argv) {

  __dace_init_toplevel_interstate_test();
  __program_toplevel_interstate_test();
  __dace_exit_toplevel_interstate_test();

  return 0;
}
