#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>

class Cmd {
  public:
    void ErrorWithHelpAndDie(std::string expr);
}; // namespace utils

#endif // INCLUDE_UTILS_H_