/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#ifndef INCLUDE_TOKENIZATION_H_
#define INCLUDE_TOKENIZATION_H_

#include <cctype>
#include <iostream>
#include <optional>
#include <variant>
#include <vector>

/**
 * Enumeration defining various token types for expression parsing.
 */
enum class TokenType {
    KIntLit,         // Integer literal
    KFloatLit,       // Floating-point literal
    KAddition,       // Addition operator '+'
    KDivision,       // Division operator '/'
    KSubtraction,    // Subtraction operator '-'
    KMultiplication, // Multiplication operator '*'
    KExponentiation, // Exponentiation operator '^'
    KOpenParen,      // Opening parenthesis '('
    KCloseParen,     // Closing parenthesis ')'
};

/**
 * Struct representing a token, consisting of a token type and an optional
 * value.
 */
struct Token {
    TokenType token_type;
    std::optional<std::string> value{};
};

struct TokenizationError {
    std::string err_msg;
};

struct TokenizationVisitor {
    std::vector<Token> operator()(TokenizationError &err) {
        std::cerr << err.err_msg << std::endl;
        std::exit(EXIT_FAILURE);
    };

    std::vector<Token> operator()(std::vector<Token> &tokens) { return tokens; }
};

/**
 * Class for tokenizing expressions provided as command line arguments.
 */
class Tokenizer {
private:
    /**
     * The expression to tokenize.
     */
    std::string m_expr;
    /**
     * The current index of the expression being tokenized.
     */
    size_t m_idx = 0;

    /**
     * Peek at the next character in the expression without consuming it.
     * @return An optional char representing the next character, if available.
     */
    inline std::optional<char> peek();

    /**
     * Consume the next character in the expression.
     * @return The consumed character.
     */
    inline char consume();

    Token TokenizeNumericValue();

public:
    explicit Tokenizer(std::string expr) : m_expr(std::move(expr)) {}

    /**
     * Tokenizes the math expression
     *
     * @return A vector of Token objects representing the parsed tokens.
     */
    std::variant<std::vector<Token>, TokenizationError>
    TokenizeExpression();
}; // class Tokenizer

#endif // INCLUDE_TOKENIZATION_H_

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
