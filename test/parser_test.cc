#include "parser.h"
#include <gtest/gtest.h>

// Test case for a successful parsing scenario.
TEST(ParserTest, SuccessfulParsing) {
  // Create a vector of tokens that represent a valid arithmetic expression.
  std::vector<Token> tokens = {
      {TokenType::KIntLit, "5"},
      {TokenType::KAddition, "+"},
      {TokenType::KIntLit, "3"},
  };

  // Create a Parser object with the tokens.
  Parser parser(tokens);

  // Parse the tokens into an AST.
  auto result = parser.ParseTokensIntoAST();

  // Check if the result is an AST.
  ASSERT_TRUE(std::holds_alternative<AST>(result));
}

// Test case for an unsuccessful parsing scenario.
TEST(ParserTest, ParsingError) {
  // Create a vector of tokens that represent an invalid expression.
  std::vector<Token> tokens = {
      {TokenType::KIntLit, "5"}, {TokenType::KAddition, "+"},
      // Missing operand here intentionally.
  };

  // Create a Parser object with the tokens.
  Parser parser(tokens);

  // Parse the tokens into an AST.
  auto result = parser.ParseTokensIntoAST();

  // Check if the result is a ParserError.
  ASSERT_TRUE(std::holds_alternative<ParserError>(result));
}
