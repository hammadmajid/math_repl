#include <iostream>
#include <tclap/CmdLine.h>

int main(int argc, char *argv[]) {

  std::string source_path; ///< path to source file that will be compiled

  try {
    // add the command line object
    // describe the program and it's version
    TCLAP::CmdLine cmd("Tstar: An experimental programming language", ' ',
                       "0.1.0");

    // value argument to get path to source file
    TCLAP::ValueArg<std::string> source_arg("s", "source",
                                            "Path to source file", true,
                                            "homer", "path/to/source.tstar");

    cmd.add(source_arg);
    cmd.parse(argc, argv);

    source_path = source_arg.getValue();

  } catch (TCLAP::ArgException &e) {
    std::cerr << "error: " << e.error() << " for arg " << e.argId()
              << std::endl;
  }

  std::cout << source_path << std::endl;

  // TODO: validate that source_path is correct

  return EXIT_SUCCESS;
}
