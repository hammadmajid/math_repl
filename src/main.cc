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

    std::variant<std::string, CmdFlag> cmd_result =
            CmdLine::ParseArgs(argc, argv);

    std::string expr;

    if (std::holds_alternative<CmdFlag>(
            cmd_result)) { // Handle the case where a command flag was provided.
        CmdFlag flag = std::get<CmdFlag>(cmd_result);
        if (flag == CmdFlag::Version) {
            std::cout << "0.1.1-pre-release" << std::endl;
            return EXIT_SUCCESS;
        } else { // Handle the case where a string (expression) was provided.
            std::cout << std::endl << "Usage:" << std::endl
                      << "\tmee \"math expression\" | [option]" << std::endl
                      << std::endl
                      << "Options:" << std::endl
                      << "\t--version Print version info and die" << std::endl
                      << "\t--help Print help and die" << std::endl
                      << std::endl
                      << "Examples:" << std::endl
                      << "\tmee \"3 + 2^4\"" << std::endl
                      << "\tmee \"20 * ( 12 / 18)\"" << std::endl
                      << "\tmee \"5!\"" << std::endl
                      << "\tmee --version" << std::endl;
            return EXIT_SUCCESS;
        }
    } else {
        expr = std::get<std::string>(cmd_result);
    }

    Tokenizer tokenizer(expr);
    std::variant<std::vector<Token>, TokenizationError> tokenization_result =
            tokenizer.TokenizeExpression();

    std::vector<Token> infix_tokens =
            std::visit(TokenizationVisitor{}, tokenization_result);

    Parser parser(infix_tokens);
    std::variant<std::vector<Token>, ParserError> parser_result = parser.ConvertToPostFixNotation();

    if (std::holds_alternative<ParserError>(parser_result)) {
        const auto [type, msg] = std::get<ParserError>(parser_result);
        switch (type) {
            case ParserErrorType::MissingOperand:
                std::cerr << "Error: Missing operand" << std::endl;
                break;
            case ParserErrorType::MismatchedParentheses:
                std::cerr << "Error: Mismatched parentheses" << std::endl;
                break;
            case ParserErrorType::ExtraOperand:
                std::cerr << "Error: Extra operand" << std::endl;
                break;
            case ParserErrorType::InvalidExpression:
                std::cerr << "Error: Invalid expression" << std::endl;
            break;
        }
        std::cerr << msg << std::endl;
        return EXIT_FAILURE;
    }

    auto postfix_tokens = std::get<std::vector<Token>>(parser_result);

    for (auto &[token_type, value]: postfix_tokens) {
        switch (token_type) {
            case TokenType::KIntLit:
            case TokenType::KFloatLit:
                std::cout << value.value() << " ";
                break;
            case TokenType::KAddition:
                std::cout << "+" << " ";
                break;
            case TokenType::KDivision:
                std::cout << "/" << " ";
                break;
            case TokenType::KSubtraction:
                std::cout << "-" << " ";
                break;
            case TokenType::KMultiplication:
                std::cout << "*" << " ";
                break;
            case TokenType::KExponentiation:
                std::cout << "!" << " ";
                break;
        }
    }

    std::cout << std::endl;

    // TODO: Evaluate the tokens postifix notation and print the result

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
