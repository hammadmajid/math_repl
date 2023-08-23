#pragma once

#include <optional>
#include <string>
#include <vector>

enum class TokenType {
  // keywords
  _const,
  _continue,
  _else,
  _exit,
  _for,
  _if,
  _return,
  _sub,
  _var,
  // literals
  float_lit,
  int_lit,
  string_lit,
};

struct Token {
  TokenType type;
  std::optional<std::string> value{};
};

class Tokenizer {
public:
  std::vector<Token> tokenize() {
    std::vector<Token> tokens;

    return tokens;
  }

private:
  const std::string m_src;
  size_t m_index = 0;
};
