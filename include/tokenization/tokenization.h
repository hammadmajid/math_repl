#ifndef INCLUDE_TOKENIZATION_H_
#define INCLUDE_TOKENIZATION_H_

#include <cctype>
#include <iostream>
#include <optional>
#include <vector>

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
  std::vector<Token> TokenizeExpression(int argc, const char *const *argv);

  private:
    void DebugTokens(std::vector<Token> tokens);
};

#endif // INCLUDE_TOKENIZATION_H_