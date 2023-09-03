cmake_minimum_required(VERSION 3.20)

project(neon)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include_directories(include)

add_executable(neon src/main.cc src/tokenization/tokenization.cc src/cmd/cmd.cc)
