#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>

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
}; // class Cmd

#endif // INCLUDE_UTILS_H_