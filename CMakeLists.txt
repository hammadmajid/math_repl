# MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
# See the end file for full the license information

cmake_minimum_required(VERSION 3.20)

project(mee VERSION 0.1.0 LANGUAGES CXX)
set(PROJECT_DESCRIPTION "A simple math expression evaluator written in C++.")
set(PROJECT_LICENSE "MIT License")
set(PROJECT_HOMEPAGE_URL "https://github.com/hammadmajid/mee")

# Set C++ standard and compile commands export
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Set sccache 
find_program(SCCACHE sccache REQUIRED)
set(CMAKE_CXX_COMPILER_LAUNCHER ${SCCACHE})

# Include directories
include_directories(include)

# Include external dependencies using FetchContent
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# Ensure GoogleTest uses a shared CRT
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Enable testing
enable_testing()

# Define the main executable
add_executable(mee
  src/main.cc
  src/tokenization.cc
  src/cmd.cc
  src/parser.cc
)

# Define the test executable and link against GoogleTest
add_executable(tests
  src/tokenization.cc
  src/cmd.cc
  src/parser.cc
  test/tokenization_test.cc
  test/cmd_test.cc
  test/parser_test.cc
)

target_link_libraries(tests
  GTest::gtest_main
)

# Use GoogleTest to discover tests
include(GoogleTest)
gtest_discover_tests(tests)

# Display project information
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "License: ${PROJECT_LICENSE}")
message(STATUS "Homepage: ${PROJECT_HOMEPAGE_URL}")
message(STATUS "Description: ${PROJECT_DESCRIPTION}")


# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS," WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
