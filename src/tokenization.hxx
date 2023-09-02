#pragma once

#include <iostream>
#include <optional>
#include <vector>

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
      exit_with_usage_guide("");
    }

    // TODO

    return tokens;
  }

private:
  void exit_with_usage_guide(std::string expr) {
    std::cerr << "\"" << expr << "\" is not a valid expression\n\n"
              << "Usage:\n"
              << "\tneon [expression]\n\n"
              << "Examples:\n"
              << "\tneon 3 + 2^4 ==> 19\n"
              << "\tneon 20 * ( 12 / 18) ==> 13.33333\n"
              << "\tneon 5! ==> 120\n";

    std::exit(EXIT_FAILURE);
  }
};
