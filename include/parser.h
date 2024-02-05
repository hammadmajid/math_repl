#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <stack>
#include <variant>
#include <vector>

#include <tokenization.h>

/**
 * Represents an error that can occur during parsing.
 */
struct ParserError {
    std::string err_msg; /**< The error message. */
};

/**
 * A parser for converting the infix mathemetical expression into a postfix
 * one. Using the Shaunting Yard algorithm.
 */
class Parser {
public:
    /**
     * @brief Constructs a Parser object with a vector of tokens for parsing.
     *
     * This constructor initializes a Parser object with the provided vector of
     * tokens, which will be used for converting into postfix notation.
     *
     * @param tokens A vector of tokens to be parsed.
     */
    explicit Parser(std::vector<Token> tokens) : m_tokens(std::move(tokens)) {
    }

    /**
     * Converts infix notation tokens into postfix (reverse polish) notation.
     * @return A std::variant containing either the vector containg Reverse Polish
     * notation of tokens or a ParserError if parsing fails.
     */
    std::variant<std::vector<Token>, ParserError> ConvertToPostFixNotation();

private:
    std::vector<Token> m_tokens; /**< The vector of tokens to be parsed. */
    size_t m_idx = 0; /**< The current index in the token vector. */

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
