/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>
#include <string.h>
#include <vector>

/**
 * The class provides some utilites to change the behaviour
 * of the program at runtime
 */
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
