#include "tokenization/tokenization.h"
#include <gtest/gtest.h>

TEST(TokenizerTest, TestIntegerLiteral) {
  Tokenizer tokenizer;
  std::string expr = "42";
  std::variant<std::vector<Token>, TokenizationError> result =
      tokenizer.TokenizeExpression(expr);
  ASSERT_TRUE(std::holds_alternative<std::vector<Token>>(result));

  std::vector<Token> tokens = std::get<std::vector<Token>>(result);
  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].token_type, TokenType::KIntLit);
  ASSERT_EQ(tokens[0].value, "42");
}

TEST(TokenizerTest, TestFloatLiteral) {
  Tokenizer tokenizer;
  std::string expr = "3.14";
  std::variant<std::vector<Token>, TokenizationError> result =
      tokenizer.TokenizeExpression(expr);
  ASSERT_TRUE(std::holds_alternative<std::vector<Token>>(result));

  std::vector<Token> tokens = std::get<std::vector<Token>>(result);
  ASSERT_EQ(tokens.size(), 1);
  ASSERT_EQ(tokens[0].token_type, TokenType::KFloatLit);
  ASSERT_EQ(tokens[0].value, "3.14");
}

TEST(TokenizerTest, TestOperatorsAndParentheses) {
  Tokenizer tokenizer;
  std::string expr = "(1 + 2) * 3 - 4 / 5 ^ 6!";
  std::variant<std::vector<Token>, TokenizationError> result =
      tokenizer.TokenizeExpression(expr);
  ASSERT_TRUE(std::holds_alternative<std::vector<Token>>(result));

  std::vector<Token> tokens = std::get<std::vector<Token>>(result);
  ASSERT_EQ(tokens.size(), 14);

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
  ASSERT_EQ(tokens[13].token_type, TokenType::KFactorial);
}

TEST(TokenizerTest, TestInvalidExpression) {
  Tokenizer tokenizer;
  std::string expr = "2 + abc";
  std::variant<std::vector<Token>, TokenizationError> result =
      tokenizer.TokenizeExpression(expr);
  ASSERT_TRUE(std::holds_alternative<TokenizationError>(result));
}
