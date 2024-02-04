/**
 * MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
 * See the end file for full the license information
 */

#include "tokenization.h"
#include <gtest/gtest.h>

TEST(TokenizerTest, TestIntegerLiteral) {
    std::string expr = "42";
    Tokenizer tokenizer(expr);
    std::variant<std::vector<Token>, TokenizationError> result =
            tokenizer.TokenizeExpression();
    ASSERT_TRUE(std::holds_alternative<std::vector<Token>>(result));

    std::vector<Token> tokens = std::get<std::vector<Token>>(result);
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens[0].token_type, TokenType::KIntLit);
    ASSERT_EQ(tokens[0].value, "42");
}

TEST(TokenizerTest, TestFloatLiteral) {
    std::string expr = "3.14";
    Tokenizer tokenizer(expr);
    std::variant<std::vector<Token>, TokenizationError> result =
            tokenizer.TokenizeExpression();
    ASSERT_TRUE(std::holds_alternative<std::vector<Token>>(result));

    std::vector<Token> tokens = std::get<std::vector<Token>>(result);
    ASSERT_EQ(tokens.size(), 1);
    ASSERT_EQ(tokens[0].token_type, TokenType::KFloatLit);
    ASSERT_EQ(tokens[0].value, "3.14");
}

TEST(TokenizerTest, TestOperatorsAndParentheses) {
    std::string expr = "(1 + 2) * 3 - 4 / 5 ^ 6";
    Tokenizer tokenizer(expr);
    std::variant<std::vector<Token>, TokenizationError> result =
            tokenizer.TokenizeExpression();
    ASSERT_TRUE(std::holds_alternative<std::vector<Token>>(result));

    std::vector<Token> tokens = std::get<std::vector<Token>>(result);
    ASSERT_EQ(tokens.size(), 13);

    // Verify the token types and values
    ASSERT_EQ(tokens[0].token_type, TokenType::KOpenParen);
    ASSERT_EQ(tokens[1].token_type, TokenType::KIntLit);
    ASSERT_EQ(tokens[1].value, "1");
    ASSERT_EQ(tokens[2].token_type, TokenType::KAddition);
    ASSERT_EQ(tokens[3].token_type, TokenType::KIntLit);
    ASSERT_EQ(tokens[3].value, "2");
    ASSERT_EQ(tokens[4].token_type, TokenType::KCloseParen);
    ASSERT_EQ(tokens[5].token_type, TokenType::KMultiplication);
    ASSERT_EQ(tokens[6].token_type, TokenType::KIntLit);
    ASSERT_EQ(tokens[6].value, "3");
    ASSERT_EQ(tokens[7].token_type, TokenType::KSubtraction);
    ASSERT_EQ(tokens[8].token_type, TokenType::KIntLit);
    ASSERT_EQ(tokens[8].value, "4");
    ASSERT_EQ(tokens[9].token_type, TokenType::KDivision);
    ASSERT_EQ(tokens[10].token_type, TokenType::KIntLit);
    ASSERT_EQ(tokens[10].value, "5");
    ASSERT_EQ(tokens[11].token_type, TokenType::KExponentiation);
    ASSERT_EQ(tokens[12].token_type, TokenType::KIntLit);
    ASSERT_EQ(tokens[12].value, "6");
}

TEST(TokenizerTest, TestInvalidExpression) {
    std::string expr = "2 + abc";
    Tokenizer tokenizer(expr);
    std::variant<std::vector<Token>, TokenizationError> result =
            tokenizer.TokenizeExpression();
    ASSERT_TRUE(std::holds_alternative<TokenizationError>(result));
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
