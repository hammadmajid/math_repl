#include "cmd/cmd.h"
#include "tokenization/tokenization.h"
#include <vector>

int main(int argc, char *argv[]) {
  Cmd cmd;
  std::string expr = cmd.ParseArgvForExprAndSetFlags(argc, argv);

  Tokenizer tokenizer;
  std::vector<Token> tokens = tokenizer.TokenizeExpression(expr);

  return EXIT_SUCCESS;
}
