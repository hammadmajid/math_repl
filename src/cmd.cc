/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "cmd.h"

CmdInput CmdLine::ParseArgvForExprAndSetFlags(int argc,
                                              const char *const *argv) {
  if (argc == 1 || argc > 5) {
    return CmdInput{CmdError{"Couldn't process arguments"}};
  }

  std::vector<std::string> args;
  std::string expr;

  for (int i = 1; i < argc; i++) {
    if (strcmp(argv[i], "--version") == 0) {
      return CmdInput{CmdFlag::VersionFlag};
    } else if (strcmp(argv[i], "--help") == 0) {
      return CmdInput{CmdFlag::HelpFlag};
    } else {
      expr = argv[i];
    }
  }

  return CmdInput{expr};
}

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
