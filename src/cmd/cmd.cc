#include "cmd/cmd.h"

bool g_debug_mode = false;

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

std::string Cmd::ParseArgvForExprAndSetFlags(int argc,
                                             const char *const *argv) {
  if (argc == 1 || argc > 4) {
    ErrorWithHelpAndDie("Couldn't process arguments");
  }

  std::vector<std::string> args;
  std::string expr;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--version") == 0) {
      std::cout << "0.1.0-pre-release" << std::endl;
      std::exit(EXIT_SUCCESS);
    } else if (strcmp(argv[i], "--debug") == 0) {
      g_debug_mode = true;
    } else {
      expr = argv[i];
    }
  }

  return expr;
}
