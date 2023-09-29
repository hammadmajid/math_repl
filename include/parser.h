#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <variant>
#include <vector>

#include <tokenization.h>

struct Expr;

/**
 * Represents an arithmetic expression node for addition.
 */
struct NodeAdd {
  Expr *left;  /**< Pointer to the left operand. */
  Expr *right; /**< Pointer to the right operand. */
};

/**
 * Represents an arithmetic expression node for subtraction.
 */
struct NodeSub {
  Expr *left;  /**< Pointer to the left operand. */
  Expr *right; /**< Pointer to the right operand. */
};

/**
 * Represents an arithmetic expression node for multiplication.
 */
struct NodeMul {
  Expr *left;  /**< Pointer to the left operand. */
  Expr *right; /**< Pointer to the right operand. */
};

/**
 * Represents an arithmetic expression node for division.
 */
struct NodeDiv {
  Expr *left;  /**< Pointer to the left operand. */
  Expr *right; /**< Pointer to the right operand. */
};

/**
 * Represents an arithmetic expression node for factorial.
 */
struct NodeFac {
  unsigned int num; /**< The non-negative integer for which the factorial is
                       calculated.  */
};

/**
 * Represents an arithmetic expression node for exponentiation.
 */
struct NodeExp {
  Expr *base;  /**< Pointer to the base expression. */
  Expr *power; /**< Pointer to the power expression. */
};

/**
 * Represents an arithmetic expression.
 */
struct Expr {
  std::variant<NodeAdd, NodeSub, NodeMul, NodeDiv, NodeFac, NodeExp>
      expr; /**< The expression variant. */
};

/**
 * Represents an Abstract Syntax Tree (AST) for arithmetic expressions.
 */
struct AST {
  std::vector<Expr> exprs; /**< Vector of arithmetic expressions. */
};

/**
 * Represents an error that can occur during parsing.
 */
struct ParserError {
  std::string err_msg; /**< The error message. */
};

/**
 * A parser for processing tokens into an Abstract Syntax Tree (AST).
 */
class Parser {
public:
  /**
   * @brief Constructs a Parser object with a vector of tokens for parsing.
   *
   * This constructor initializes a Parser object with the provided vector of
   * tokens, which will be used for parsing into an Abstract Syntax Tree (AST).
   *
   * @param tokens A vector of tokens to be parsed.
   */
  explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {}

  /**
   * Parses tokens into an Abstract Syntax Tree (AST).
   * @return A std::variant containing either the AST or a ParserError if
   * parsing fails.
   */
  std::variant<AST, ParserError> ParseTokensIntoAST();

private:
  std::vector<Token> m_tokens; /**< The vector of tokens to be parsed. */
  size_t m_idx = 0;                /**< The current index in the token vector. */

  /**
   * Peek at the next token in the token vector without consuming it.
   * @return An optional Token representing the next token, if available.
   */
  [[nodiscard]] inline std::optional<Token> peek();

  /**
   * Consume the next token in the token vector.
   * @return The consumed Token.
   */
  inline Token consume();
};

#endif // INCLUDE_PARSER_H_
