#include <iostream>

int main(int argc, char *argv[]) {

  std::cout << "neon: math expression evaluater\n\n"
            << "Usage:\n"
            << "\tneon [expression]\n\n"
            << "Examples:\n"
            << "\tneon 3 + 2^4 ==> 19\n"
            << "\tneon 20 * ( 12 / 18) ==> 13.33333\n"
            << "\tneon 5! ==> 120\n";

  return EXIT_SUCCESS;
}
