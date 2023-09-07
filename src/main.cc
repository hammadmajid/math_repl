/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "cmd/cmd.h"
#include "tokenization/tokenization.h"
#include <iostream>
#include <variant>
#include <vector>

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

int main(int argc, char *argv[]) {

  CmdLine cmd;
  CmdInput cmd_input = cmd.ParseArgvForExprAndSetFlags(argc, argv);

  std::string expr = std::visit(CmdVisitor{}, cmd_input.input);

  Tokenizer tokenizer;
  std::vector<Token> tokens = tokenizer.TokenizeExpression(expr);

  return EXIT_SUCCESS;
}

/**
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to
deal
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
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/
