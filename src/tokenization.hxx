#pragma once

#include <iostream>
#include <optional>
#include <vector>

#include "utils.hxx"

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
        // TODO
      }
    }

    return tokens;
  }
};
