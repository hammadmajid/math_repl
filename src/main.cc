#include "tokenization/tokenization.h"
#include <vector>

int main(int argc, char *argv[]) {

  Tokenizer tokenizer;
  std::vector<Token> tokens = tokenizer.TokenizeExpression(argc, argv);

  return EXIT_SUCCESS;
}
