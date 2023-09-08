/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "cmd.h"
#include "tokenization.h"
#include <iostream>
#include <variant>
#include <vector>

int main(int argc, char *argv[]) {

  CmdLine cmd_line;
  std::variant<std::string, CmdFlag> cmd_result =
      cmd_line.ParseArgvForExprAndSetFlags(argc, argv);

  std::string expr;

  if (std::holds_alternative<CmdFlag>(
          cmd_result)) { // Handle the case where a command flag was provided.
    CmdFlag flag = std::get<CmdFlag>(cmd_result);
    if (flag == CmdFlag::Version) {
      std::cout << "0.1.1-pre-release" << std::endl;
      return EXIT_SUCCESS;
    } else { // Handle the case where a string (expression) was provided.
      // TODO: print help
      std::cout << "TODO: Print help and exit" << std::endl;
      return EXIT_SUCCESS;
    }
  } else {
    expr = std::get<std::string>(cmd_result);
  }

  Tokenizer tokenizer;
  std::variant<std::vector<Token>, TokenizationError> tokekization_result =
      tokenizer.TokenizeExpression(expr);

  std::vector<Token> tokens =
      std::visit(TokenizationVisitor{}, tokekization_result);

  // TODO: parse the tokens into AST node

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
