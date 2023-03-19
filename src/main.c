#include "cli.h"

int main(int argc, char **argv) {

  if (argc >= 1) {
    parse_args(argc, argv);
  } else {
    print_usage();
  }
  return 0;
}