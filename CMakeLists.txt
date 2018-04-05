cmake_minimum_required(VERSION 3.10)
project(SLama)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

file(GLOB SOURCE_FILES src/*)

add_subdirectory(tests)

add_library(SLama ${SOURCE_FILES})