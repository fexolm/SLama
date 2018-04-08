cmake_minimum_required(VERSION 2.8)
project(SLama)

set(CMAKE_C_STANDARD 11)

enable_testing()

file(GLOB SOURCE_FILES src/*)

add_subdirectory(tests)

add_library(SLama ${SOURCE_FILES})