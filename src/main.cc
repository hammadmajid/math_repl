#include "tokenization.hxx"
#include <vector>

int main(int argc, char *argv[]) {

  Tokenizer tokenizer;
  std::vector<Token> tokens = tokenizer.tokenize(argc, argv);

  return EXIT_SUCCESS;
}
