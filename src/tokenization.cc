/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "tokenization.h"

std::optional<char> Tokenizer::peek() {
    if (m_idx + 1 > m_expr.length()) {
        return {};
    } else {
        return m_expr.at(m_idx);
    }
}

char Tokenizer::consume() { return m_expr.at(m_idx++); }

Token Tokenizer::TokenizeNumericValue() {
    bool is_floating = false;
    std::string num_buf;
    num_buf.push_back(consume());

    while (peek().has_value() && std::isdigit(peek().value())) {
        num_buf.push_back(consume());
    }

    if (peek().has_value() && peek().value() == '.') {
        is_floating = true;
        num_buf.push_back(consume());
        while (peek().has_value() && std::isdigit(peek().value())) {
            num_buf.push_back(consume());
        }
    }

    if (is_floating) {
        return {.token_type = TokenType::KFloatLit, .value = num_buf};
    } else {
        return {.token_type = TokenType::KIntLit, .value = num_buf};
    }
}

std::variant<std::vector<Token>, TokenizationError>
Tokenizer::TokenizeExpression() {
    std::vector<Token> tokens;

    while (peek().has_value()) {
        if (std::isspace((peek().value()))) {
            consume();
        } else if (std::isdigit(peek().value())) {
            tokens.push_back(TokenizeNumericValue());
        } else if (peek().value() == '+') {
            consume();
            tokens.push_back({.token_type = TokenType::KAddition});
        } else if (peek().value() == '-') {
            consume();
            tokens.push_back({.token_type = TokenType::KSubtraction});
        } else if (peek().value() == '*') {
            consume();
            tokens.push_back({.token_type = TokenType::KMultiplication});
        } else if (peek().value() == '/') {
            consume();
            tokens.push_back({.token_type = TokenType::KDivision});
        } else if (peek().value() == '^') {
            consume();
            tokens.push_back({.token_type = TokenType::KExponentiation});
        } else if (peek().value() == '(') {
            consume();
            tokens.push_back({.token_type = TokenType::KOpenParen});
        } else if (peek().value() == ')') {
            consume();
            tokens.push_back({.token_type = TokenType::KCloseParen});
        } else {
            return TokenizationError{
                    .err_msg = "Invalid character in expression: " +
                               std::string(1, peek().value())};
        }
    }

    return tokens;
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
