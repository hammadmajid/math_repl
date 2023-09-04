#include "tokenization/tokenization.h"
#include "cmd/cmd.h"
#include <vector>

std::vector<Token> Tokenizer::TokenizeExpression(std::string expr) {
  std::vector<Token> tokens;

  Cmd cmd;

  for (int i = 0; i < expr.length(); i++) {
    if (std::isspace(expr.at(i))) {
      continue; // Skip whitespace characters
    } else if (std::isdigit(expr.at(i))) {
      // Tokenize integer literals
      std::string buf;
      buf.push_back(expr.at(i));

      int idx = i + 1; // Next value in expr

      while (std::isdigit(expr[idx])) {
        buf.push_back(expr.at(idx));
        idx += 1;
      }

      tokens.push_back({
          .token_type = TokenType::KIntLit,
          .value = buf,
      });
    } else if (expr.at(i) == '+') {
      tokens.push_back({.token_type = TokenType::KAddition});
    } else if (expr.at(i) == '-') {
      tokens.push_back({.token_type = TokenType::KSubtraction});
    } else if (expr.at(i) == '*') {
      tokens.push_back({.token_type = TokenType::KMultiplication});
    } else if (expr.at(i) == '/') {
      tokens.push_back({.token_type = TokenType::KDivision});
    } else if (expr.at(i) == '!') {
      tokens.push_back({.token_type = TokenType::KFactorial});
    } else if (expr.at(i) == '^') {
      tokens.push_back({.token_type = TokenType::KExponentiation});
    } else if (expr.at(i) == '(') {
      tokens.push_back({.token_type = TokenType::KOpenParen});
    } else if (expr.at(i) == ')') {
      tokens.push_back({.token_type = TokenType::KCloseParen});
    } else {
      // Handle invalid characters in expressions
      cmd.ErrorWithHelpAndDie(expr + " is not a valid expression");
    }
  }

  if (g_debug_mode) {
    DebugTokens(tokens);
  }

  return tokens;
}

void Tokenizer::DebugTokens(std::vector<Token> tokens) {
  for (Token token : tokens) {
    if (token.token_type == TokenType::KIntLit) {
      std::cout << "int_lit = " << token.value.value() << std::endl;
    } else if (token.token_type == TokenType::KFloatLit) {
      std::cout << "float_lit = " << token.value.value() << std::endl;
    } else if (token.token_type == TokenType::KAddition) {
      std::cout << "+" << std::endl;
    } else if (token.token_type == TokenType::KSubtraction) {
      std::cout << "=" << std::endl;
    } else if (token.token_type == TokenType::KMultiplication) {
      std::cout << "*" << std::endl;
    } else if (token.token_type == TokenType::KDivision) {
      std::cout << "/" << std::endl;
    } else if (token.token_type == TokenType::KExponentiation) {
      std::cout << "^" << std::endl;
    } else if (token.token_type == TokenType::KFactorial) {
      std::cout << "!" << std::endl;
    } else if (token.token_type == TokenType::KOpenParen) {
      std::cout << "(" << std::endl;
    } else if (token.token_type == TokenType::KCloseParen) {
      std::cout << ")" << std::endl;
    } else {
      std::cerr << "Invalid token" << std::endl;
    }
  }
}