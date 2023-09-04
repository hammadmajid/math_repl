#include "cmd/cmd.h"

void Cmd::ErrorWithHelpAndDie(std::string err_msg) {
  std::cerr << err_msg << std::endl;

  std::cout << "Usage:" << std::endl
            << "\tneon \"[expression]\"" << std::endl
            << std::endl
            << "Examples:" << std::endl
            << "\tneon \"3 + 2^4\"" << std::endl
            << "\tneon \"20 * ( 12 / 18)\"" << std::endl
            << "\tneon \"5!\"" << std::endl;

  std::exit(EXIT_FAILURE);
}
