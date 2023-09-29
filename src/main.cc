/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "cmd.h"
#include "tokenization.h"
#include <cstdlib>
#include <parser.h>
#include <variant>

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
        std::cout << std::endl << "Usage:" << std::endl
          << "\tneon \"math expression\" | [option]" << std::endl
          << std::endl
          << "Options:" << std::endl
          << "\t--version Print version info and die" << std::endl
          << "\t--help Print help and die" << std::endl
          << std::endl
          << "Examples:" << std::endl
          << "\tneon \"3 + 2^4\"" << std::endl
          << "\tneon \"20 * ( 12 / 18)\"" << std::endl
          << "\tneon \"5!\"" << std::endl
          << "\tneon --version" << std::endl;
        return EXIT_SUCCESS;
    }
  } else {
    expr = std::get<std::string>(cmd_result);
  }

  Tokenizer tokenizer(expr);
  std::variant<std::vector<Token>, TokenizationError> tokenization_result =
      tokenizer.TokenizeExpression();

  std::vector<Token> tokens =
      std::visit(TokenizationVisitor{}, tokenization_result);

  Parser parser(tokens);
  std::variant<AST, ParserError> parser_result = parser.ParseTokensIntoAST();

  if (std::holds_alternative<ParserError>(parser_result)) {
    ParserError err = std::get<ParserError>(parser_result);
    std::cerr << err.err_msg << std::endl;
    std::exit(EXIT_FAILURE);
  }

  AST ast = std::get<AST>(parser_result);

  // Evaluate each node on AST and print the final result

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
