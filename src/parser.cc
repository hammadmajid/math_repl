/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include <stack>

#include "parser.h"

std::optional<Token> Parser::peek() {
    if (m_idx < m_tokens.size()) {
        return m_tokens[m_idx];
    }

    return {};
}

Token Parser::consume() { return m_tokens.at(m_idx++); }

unsigned short int Parser::GetOperatorPrecedence(const TokenType type)  {
    if (type == TokenType::KAddition || type == TokenType::KSubtraction) {
        return 1;
    }
    if (type == TokenType::KDivision || type == TokenType::KMultiplication) {
        return 2;
    }
    if (type == TokenType::KExponentiation) {
        return 3;
    }

    return 0;
}

std::variant<std::vector<Token>, ParserError> Parser::ConvertToPostFixNotation() {
    std::vector<Token> postfix_tokens;
    std::stack<Token> operator_stack;

    while (auto maybe_token = peek()) {
        switch (Token token = maybe_token.value(); token.token_type) {
            case TokenType::KIntLit:
            case TokenType::KFloatLit:
                postfix_tokens.push_back(token);
                consume();
                break;
            case TokenType::KAddition:
            case TokenType::KDivision:
            case TokenType::KSubtraction:
            case TokenType::KMultiplication:
            case TokenType::KExponentiation:
                while (!operator_stack.empty() &&
                       GetOperatorPrecedence(operator_stack.top().token_type) >=
                           GetOperatorPrecedence(token.token_type)) {
                    postfix_tokens.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                operator_stack.push(token);
                consume();
                break;
            case TokenType::KOpenParen:
                operator_stack.push(token);
                consume();
                break;
            case TokenType::KCloseParen:
                while (!operator_stack.empty() &&
                       operator_stack.top().token_type != TokenType::KOpenParen) {
                    postfix_tokens.push_back(operator_stack.top());
                    operator_stack.pop();
                }
                if (operator_stack.empty() ||
                    operator_stack.top().token_type != TokenType::KOpenParen) {
                    // Error: mismatched parentheses
                    return ParserError{ParserErrorType::MismatchedParentheses,
                                       "Mismatched parentheses in expression."};
                }
                operator_stack.pop(); // Discard the left parenthesis
                consume();
                break;
        }
    }

    // Pop any remaining operators from the stack
    while (!operator_stack.empty()) {
        if (operator_stack.top().token_type == TokenType::KOpenParen) {
            // Error: unmatched left parenthesis
            return ParserError{ParserErrorType::MismatchedParentheses,
                               "Unmatched left parenthesis in expression."};
        }
        postfix_tokens.push_back(operator_stack.top());
        operator_stack.pop();
    }

    return postfix_tokens;
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
