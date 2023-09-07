/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>
#include <optional>
#include <string.h>
#include <variant>
#include <vector>

enum class CmdFlag {
  VersionFlag,
  HelpFlag,
};

struct CmdError {
  std::string err_msg;
};

struct CmdInput {
  std::variant<std::string, CmdError, CmdFlag> input;
};

struct CmdVisitor {
  std::string operator()(CmdError &err) {
    std::cerr << err.err_msg << std::endl;
    std::exit(EXIT_FAILURE);
  };

  std::string operator()(CmdFlag &flag) {
    if (flag == CmdFlag::VersionFlag) {
      std::cout << "0.1.0-pre-release" << std::endl;
      std::exit(EXIT_SUCCESS);
    } else {
      std::cout << "Usage:" << std::endl
                << "\tneon \"[expression]\"" << std::endl
                << std::endl
                << "Examples:" << std::endl
                << "\tneon \"3 + 2^4\"" << std::endl
                << "\tneon \"20 * ( 12 / 18)\"" << std::endl
                << "\tneon \"5!\"" << std::endl;

      std::exit(EXIT_SUCCESS);
    }
  };

  std::string operator()(std::string &expr) { return expr; }
};

/**
 * The class provides some utilites to change the behaviour
 * of the program at runtime
 */
class CmdLine {
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
   * @return CmdInput which contains a variant of either std::string, CmdError,
   * CmdFlag
   */
  CmdInput ParseArgvForExprAndSetFlags(int argc, const char *const *argv);
}; // class Cmd

#endif // INCLUDE_CMD_H_

/**
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
