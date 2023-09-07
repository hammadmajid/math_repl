#include "cmd/cmd.h"
#include "tokenization/tokenization.h"
#include <gtest/gtest.h>
#include <vector>

TEST(TokenizationTest, TestTokenizeExpression) {

  /* Arrange */
  Tokenizer tokenizer;
  std::string test_expr = "1 + 2.0 - 3 * 4/(5!)";

  /* Define the expected tokens */
  std::vector<Token> expected_tokens = {
      {TokenType::KIntLit, "1"},     {TokenType::KAddition},
      {TokenType::KFloatLit, "2.0"}, {TokenType::KSubtraction},
      {TokenType::KIntLit, "3"},     {TokenType::KMultiplication},
      {TokenType::KIntLit, "4"},     {TokenType::KDivision},
      {TokenType::KOpenParen},       {TokenType::KIntLit, "5"},
      {TokenType::KFactorial},       {TokenType::KCloseParen}};

  /* Act */
  std::vector<Token> actual_tokens = tokenizer.TokenizeExpression(test_expr);

  /* Assert */
  ASSERT_EQ(actual_tokens.size(), expected_tokens.size());

  for (size_t i = 0; i < actual_tokens.size(); ++i) {
    ASSERT_EQ(actual_tokens[i].token_type, expected_tokens[i].token_type);
    ASSERT_EQ(actual_tokens[i].value, expected_tokens[i].value);
  }
}