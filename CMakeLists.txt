# MIT License Copyright (c) 2023 Hammad Majid (hammadmajid@proton.me)
# See the end file for full the license

cmake_minimum_required(VERSION 3.20)

project(neon)

set(PROJECT_NAME "neon")
set(PROJECT_VERSION "0.1.0-pre-release")
set(PROJECT_LICENSE "MIT License")
set(PROJECT_HOMEPAGE_URL "https://github.com/hammadmajid/neon")
set(PROJECT_DESCRIPTION "A simple math expression evaluator written in C++.")

message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "Version: ${PROJECT_VERSION}")
message(STATUS "License: ${PROJECT_LICENSE}")
message(STATUS "Homepage: ${PROJECT_HOMEPAGE_URL}")
message(STATUS "Description: ${PROJECT_DESCRIPTION}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

include_directories(include)

add_executable(neon src/main.cc src/tokenization/tokenization.cc src/cmd/cmd.cc)

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
