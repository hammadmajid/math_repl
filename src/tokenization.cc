/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "tokenization.h"
#include <vector>

std::variant<std::vector<Token>, TokenizationError>
Tokenizer::TokenizeExpression() {
  std::vector<Token> tokens;

  for (int i = 0; i < m_expr.length(); i++) {
    if (std::isspace(m_expr.at(i))) {
      continue; /* Skip whitespace characters */
    } else if (std::isdigit(m_expr.at(i)) || m_expr.at(i) == '.') {
      /* Tokenize numeric literals (both integers and floating-point numbers) */
      std::string buf;
      buf.push_back(m_expr.at(i));

      int idx = i + 1; /* Next value in expr */
      bool isFloatingPoint = false;

      while (std::isdigit(m_expr[idx]) ||
             (m_expr[idx] == '.' && !isFloatingPoint)) {
        if (m_expr[idx] == '.') {
          isFloatingPoint = true;
        }
        buf.push_back(m_expr.at(idx));
        idx += 1;
      }

      if (isFloatingPoint) {
        tokens.push_back({
            .token_type = TokenType::KFloatLit,
            .value = buf,
        });
      } else {
        tokens.push_back({
            .token_type = TokenType::KIntLit,
            .value = buf,
        });
      }

      i = idx - 1;
    } else if (m_expr.at(i) == '+') {
      tokens.push_back({.token_type = TokenType::KAddition});
    } else if (m_expr.at(i) == '-') {
      tokens.push_back({.token_type = TokenType::KSubtraction});
    } else if (m_expr.at(i) == '*') {
      tokens.push_back({.token_type = TokenType::KMultiplication});
    } else if (m_expr.at(i) == '/') {
      tokens.push_back({.token_type = TokenType::KDivision});
    } else if (m_expr.at(i) == '!') {
      tokens.push_back({.token_type = TokenType::KFactorial});
    } else if (m_expr.at(i) == '^') {
      tokens.push_back({.token_type = TokenType::KExponentiation});
    } else if (m_expr.at(i) == '(') {
      tokens.push_back({.token_type = TokenType::KOpenParen});
    } else if (m_expr.at(i) == ')') {
      tokens.push_back({.token_type = TokenType::KCloseParen});
    } else {
      return TokenizationError{.err_msg = m_expr + "is not a valid expression"};
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
