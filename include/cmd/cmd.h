#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>
#include <string.h>
#include <vector>

// The class provides some utilites to change the behaviour
// of the program at runtime
class Cmd {
public:
  /** This function prints an error message to the standard
   * error stream, followed by the program's usage message,
   * and then exits the program with a status of 1.
   * @param err_msg The error message to print
   */
  void ErrorWithHelpAndDie(std::string err_msg);

  /** Parses command-line arguments and sets flags based on them.
   * @param argc The number of command-line arguments, including the program
   * name.
   * @param argv An array of C-style strings representing the command-line
   * arguments.
   * @return A string containing the math expression
   */
  std::string ParseArgvForExprAndSetFlags(int argc, const char *const *argv);
}; // class Cmd

/**
 * When true, the program will print additional information at every step for
 * debugging. Will be set to true if "--debug" flag is passed as argument
 */
extern bool g_debug_mode;

#endif // INCLUDE_UTILS_H_