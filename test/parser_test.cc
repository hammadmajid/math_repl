/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "parser.h"
#include <gtest/gtest.h>

// Test case for a successful parsing scenario.
TEST(ParserTest, SuccessfulParsing) {
    // Create a vector of tokens that represent a valid arithmetic expression.
    std::vector<Token> tokens = {
            {TokenType::KIntLit,   "5"},
            {TokenType::KAddition, "+"},
            {TokenType::KIntLit,   "3"},
    };

    // Create a Parser object with the tokens.
    Parser parser(tokens);

    // Convert the infix tokens into postfix ones.
    auto result = parser.ConvertToPostFixNotation();

    // Check if the result is a stack of Token.
    ASSERT_TRUE(std::holds_alternative<std::vector<Token>>(result));
}

// Test case for an unsuccessful parsing scenario.
TEST(ParserTest, ParsingError) {
    // Create a vector of tokens that represent an invalid expression.
    std::vector<Token> tokens = {
            {TokenType::KIntLit,   "5"},
            {TokenType::KAddition, "+"},
            // Missing operand here intentionally.
    };

    // Create a Parser object with the tokens.
    Parser parser(tokens);

    // Convert the infix tokens into postfix ones.
    auto result = parser.ConvertToPostFixNotation();

    // Check if the result is a ParserError.
    ASSERT_TRUE(std::holds_alternative<ParserError>(result));
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
