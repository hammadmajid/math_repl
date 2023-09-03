#pragma once

#include <cctype>
#include <iostream>
#include <optional>
#include <vector>

#include "utils.h"

enum class TokenType {
  KIntLit,
  KFloatLit,
  KAddition,
  KDivision,
  KSubstraction,
  KMultiplication,
  KExponentiation,
  KFactorial,
  KOpenParen,
  KCloseParen,
};

struct Token {
  TokenType token_type;
  std::optional<std::string> value{};
};

class Tokenizer {
public:
  std::vector<Token> TokenizeExpression(int argc, const char *const *argv) {
    std::vector<Token> tokens;

    if (argc == 1) {
      utils::PrintHelpAndDie("null");
    }

    std::vector<std::string> args;

    for (int i = 1; i < argc; i++) {
      args.push_back(argv[i]);
    }

    for (std::string arg : args) {
      for (int i = 0; i < arg.length(); i++) {
        if (std::isspace(arg.at(i))) {
          continue;
        } else if (std::isdigit(arg.at(i))) {
          std::string buf;
          buf.push_back(arg.at(i));

          int idx = i + 1; // next value in arg

          while (std::isdigit(arg[idx])) {
            buf.push_back(arg.at(idx));
            idx += 1;
          }

          tokens.push_back({
              .token_type = TokenType::KIntLit,
              .value = buf,
          });
        } else if (arg.at(i) == '+') {
          tokens.push_back({.token_type = TokenType::KAddition});
        } else if (arg.at(i) == '-') {
          tokens.push_back({.token_type = TokenType::KSubstraction});
        } else if (arg.at(i) == '*') {
          tokens.push_back({.token_type = TokenType::KMultiplication});
        } else if (arg.at(i) == '/') {
          tokens.push_back({.token_type = TokenType::KDivision});
        } else if (arg.at(i) == '!') {
          tokens.push_back({.token_type = TokenType::KFactorial});
        } else if (arg.at(i) == '^') {
          tokens.push_back({.token_type = TokenType::KExponentiation});
        } else if (arg.at(i) == '(') {
          tokens.push_back({.token_type = TokenType::KOpenParen});
        } else if (arg.at(i) == ')') {
          tokens.push_back({.token_type = TokenType::KCloseParen});
        } else {
          utils::PrintHelpAndDie(arg);
        }
      }
    }

    DebugTokens(tokens);

    return tokens;
  }

  private:
    void DebugTokens(std::vector<Token> tokens) {
      for (Token token : tokens) {
        if (token.token_type == TokenType::KIntLit) {
          std::cout << "int_lit = " << token.value.value() << std::endl;
        } else if (token.token_type == TokenType::KFloatLit) {
          std::cout << "float_lit = " << token.value.value() << std::endl;
        } else if (token.token_type == TokenType::KAddition) {
          std::cout << "+" << std::endl;
        } else if (token.token_type == TokenType::KSubstraction) {
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
};
