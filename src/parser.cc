#include "parser.h"

std::variant<AST, ParserError> Parser::ParseTokensIntoAST() {
  return ParserError{
      .err_msg = "Failed to parse tokens into AST, function no implemented yet."};
}

