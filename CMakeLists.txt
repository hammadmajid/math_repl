cmake_minimum_required(VERSION 3.20)

project(tstar)

set(CMAKE_CXX_STANDARD 17)

include_directories( BEFORE include/tclap/include )

add_executable(tstar src/main.cxx)

