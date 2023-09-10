#include "parser.h"

std::optional<Token> Parser::peek() {
  if (m_idx + 1 >= m_tokens.size()) {
    return m_tokens.at(m_idx);
  } else {
    return {};
  }
}

Token Parser::consume() { return m_tokens.at(m_idx++); }

std::variant<AST, ParserError> Parser::ParseTokensIntoAST() {
  return ParserError{
      .err_msg = "Failed to parse tokens into AST, function no implemented yet."};
}
