#include "cmd/cmd.h"
#include "tokenization/tokenization.h"
#include <gtest/gtest.h>
#include <vector>

TEST(test_tokenization, test_tokenize_expression) {
  Tokenizer tokenizer;

  std::string test_expr = "1 + 2.0 - 3 * 4/(5!)";
  std::vector<Token> expected_tokens;

  expected_tokens.push_back({
      .token_type = TokenType::KIntLit,
      .value = "1",
  });

  expected_tokens.push_back({
      .token_type = TokenType::KAddition,
  });

  expected_tokens.push_back({
      .token_type = TokenType::KFloatLit,
      .value = "2.0",
  });

  expected_tokens.push_back({
      .token_type = TokenType::KSubtraction,
  });

  expected_tokens.push_back({
      .token_type = TokenType::KIntLit,
      .value = "3",
  });

  expected_tokens.push_back({
      .token_type = TokenType::KMultiplication,
  });

  expected_tokens.push_back({
      .token_type = TokenType::KIntLit,
      .value = "4",
  });

  expected_tokens.push_back({
      .token_type = TokenType::KDivision,
  });

  expected_tokens.push_back({
      .token_type = TokenType::KOpenParen,
  });

  expected_tokens.push_back({
      .token_type = TokenType::KIntLit,
      .value = "5",
  });

  expected_tokens.push_back({
      .token_type = TokenType::KFactorial,
  });

  expected_tokens.push_back({
      .token_type = TokenType::KCloseParen,
  });

  std::vector<Token> actual_tokens = tokenizer.TokenizeExpression(test_expr);

  ASSERT_EQ(actual_tokens.size(), expected_tokens.size());

  for (size_t i = 0; i < actual_tokens.size(); ++i) {
    ASSERT_EQ(actual_tokens[i].token_type, expected_tokens[i].token_type);
    ASSERT_EQ(actual_tokens[i].value, expected_tokens[i].value);
  }
}