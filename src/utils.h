#pragma once

#include <iostream>

namespace utils {
inline void PrintHelpAndDie(std::string expr) {
  std::cerr << "\"" << expr << "\" is not a valid expression\n\n"
            << "Usage:\n"
            << "\tneon [expression]\n\n"
            << "Examples:\n"
            << "\tneon 3 + 2^4 ==> 19\n"
            << "\tneon 20 * ( 12 / 18) ==> 13.33333\n"
            << "\tneon 5! ==> 120\n";

  std::exit(EXIT_FAILURE);
}
} // namespace utils
