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
