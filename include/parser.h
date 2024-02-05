/**
* MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <stack>
#include <variant>
#include <vector>

#include <tokenization.h>

/**
 * Enumeration representing various types of errors that can occur during parsing.
 */
enum class ParserErrorType {
    MissingOperand, // Every operator requires two operand, throw this if missing
    MismatchedParentheses, // Throw this if opening or closing parentheses is missing
    ExtraOperand, // Thow if there is extra operand in the expression
    InvalidExpression, // General catch-all for other errors
};

/**
 * Represents an error that can occur during parsing.
 */
struct ParserError {
    ParserErrorType type; /**< The type of error that occured. */
    std::string msg; /**< The error message. */
};

/**
 * A parser for converting the infix mathemetical expression into a postfix
 * one. Using the Shaunting Yard algorithm.
 */
class Parser {
public:
    /**
     * @brief Constructs a Parser object with a vector of tokens for parsing.
     *
     * This constructor initializes a Parser object with the provided vector of
     * tokens, which will be used for converting into postfix notation.
     *
     * @param tokens A vector of tokens to be parsed.
     */
    explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {
    }

    /**
     * Converts infix notation tokens into postfix (reverse polish) notation.
     * @return A std::variant containing either the vector containg Reverse Polish
     * notation of tokens or a ParserError if parsing fails.
     */
    std::variant<std::vector<Token>, ParserError> ConvertToPostFixNotation();

private:
    std::vector<Token> m_tokens; /**< The vector of tokens to be parsed. */
    size_t m_idx = 0; /**< The current index in the token vector. */

    /**
     * Peek at the next token in the token vector without consuming it.
     * @return An optional Token representing the next token, if available.
     */
    [[nodiscard]] inline std::optional<Token> peek();

    /**
     * Consume the next token in the token vector.
     * @return The consumed Token.
     */
    inline Token consume();

    /**
     * Calculate the precedence of the operator. The precdence as:
     * 0 - default precedence
     * 1 - low precedence
     * 2 - medium precedence
     * 3 - high precedenve
     * @param type The TokenType of the token whose precedence will be calculated
     * @return The precendenc of the operator in 0..3 range
     */
    [[nodiscard]] unsigned short int static GetOperatorPrecedence(TokenType type);
};

#endif // INCLUDE_PARSER_H_

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
