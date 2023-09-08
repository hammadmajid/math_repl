/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#ifndef INCLUDE_CMD_H_
#define INCLUDE_CMD_H_

#include <iostream>
#include <string.h>
#include <variant>

// Enumeration representing different command-line flags
enum class CmdFlag {
  Version, // Indicates a request for the version information
  Help,    // Indicates a request for help or usage information
};

/**
 * The `CmdLine` class provides utilities to parse command-line arguments
 * and set flags based on them.
 */
class CmdLine {
public:
  /**
   * Parses command-line arguments and sets flags based on them.
   *
   * @param argc The number of command-line arguments, including the program
   * name.
   * @param argv An array of C-style strings representing the command-line
   * arguments.
   *
   * @return A variant containing either a std::string or a CmdFlag.
   *         - If a valid expression is found, it returns the expression as a
   * std::string.
   *         - If a recognized flag is found, it returns the corresponding
   * CmdFlag.
   *         - If neither an expression nor a recognized flag is found, it
   * returns an empty string.
   */
  std::variant<std::string, CmdFlag>
  ParseArgvForExprAndSetFlags(int argc, const char *const *argv);
};

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
