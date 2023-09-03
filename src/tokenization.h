#pragma once

#include <cctype>
#include <iostream>
#include <optional>
#include <vector>

#include "utils.h"

enum class TokenType {
  int_lit,
  float_lit,

  addition,
  division,
  substraction,
  multiplication,
  exponentiation,
  factorial,

  open_paren,
  close_paren,
};

struct Token {
  TokenType token_type;
  std::optional<std::string> value{};
};

class Tokenizer {
public:
  std::vector<Token> tokenize(int argc, const char *const *argv) {
    std::vector<Token> tokens;

    if (argc == 1) {
      utils::exit_with_usage_guide("null");
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
              .token_type = TokenType::int_lit,
              .value = buf,
          });
        } else if (arg.at(i) == '+') {
          tokens.push_back({.token_type = TokenType::addition});
        } else if (arg.at(i) == '-') {
          tokens.push_back({.token_type = TokenType::substraction});
        } else if (arg.at(i) == '*') {
          tokens.push_back({.token_type = TokenType::multiplication});
        } else if (arg.at(i) == '/') {
          tokens.push_back({.token_type = TokenType::division});
        } else if (arg.at(i) == '!') {
          tokens.push_back({.token_type = TokenType::factorial});
        } else if (arg.at(i) == '^') {
          tokens.push_back({.token_type = TokenType::exponentiation});
        } else if (arg.at(i) == '(') {
          tokens.push_back({.token_type = TokenType::open_paren});
        } else if (arg.at(i) == ')') {
          tokens.push_back({.token_type = TokenType::close_paren});
        } else {
          utils::exit_with_usage_guide(arg);
        }
      }
    }

    debug_tokens(tokens);

    return tokens;
  }

  private:
    void debug_tokens(std::vector<Token> tokens) {
      for (Token token : tokens) {
        if (token.token_type == TokenType::int_lit) {
          std::cout << "int_lit = " << token.value.value() << std::endl;
        } else if (token.token_type == TokenType::float_lit) {
          std::cout << "float_lit = " << token.value.value() << std::endl;
        } else if (token.token_type == TokenType::addition) {
          std::cout << "+" << std::endl;
        } else if (token.token_type == TokenType::substraction) {
          std::cout << "=" << std::endl;
        } else if (token.token_type == TokenType::multiplication) {
          std::cout << "*" << std::endl;
        } else if (token.token_type == TokenType::division) {
          std::cout << "/" << std::endl;
        } else if (token.token_type == TokenType::exponentiation) {
          std::cout << "^" << std::endl;
        } else if (token.token_type == TokenType::factorial) {
          std::cout << "!" << std::endl;
        } else if (token.token_type == TokenType::open_paren) {
          std::cout << "(" << std::endl;
        } else if (token.token_type == TokenType::close_paren) {
          std::cout << ")" << std::endl;
        } else {
          std::cerr << "Invalid token" << std::endl;
        }
      }
    }
};
