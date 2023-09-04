#ifndef INCLUDE_TOKENIZATION_H_
#define INCLUDE_TOKENIZATION_H_

#include <cctype>
#include <iostream>
#include <optional>
#include <vector>

// Enumeration defining various token types for expression parsing.
enum class TokenType {
  KIntLit,         // Integer literal
  KFloatLit,       // Floating-point literal
  KAddition,       // Addition operator '+'
  KDivision,       // Division operator '/'
  KSubtraction,    // Subtraction operator '-'
  KMultiplication, // Multiplication operator '*'
  KExponentiation, // Exponentiation operator '^'
  KFactorial,      // Factorial operator '!'
  KOpenParen,      // Opening parenthesis '('
  KCloseParen,     // Closing parenthesis ')'
};

// Struct representing a token, consisting of a token type and an optional
// value.
struct Token {
  TokenType token_type;
  std::optional<std::string> value{};
};

// Class for tokenizing expressions provided as command line arguments.
class Tokenizer {
public:
  /**
   * Tokenizes the given command line arguments into a vector of Token objects.
   *
   * @param expr The math expression to tokenize
   * @return A vector of Token objects representing the parsed tokens.
   */
  std::vector<Token> TokenizeExpression(std::string expr);

private:
  /**
   * Debug function to print the tokenized tokens to the console for debugging
   * purposes.
   *
   * @param tokens The vector of Token objects to be printed.
   */
  void DebugTokens(std::vector<Token> tokens);
}; // class Tokenizer

#endif // INCLUDE_TOKENIZATION_H_