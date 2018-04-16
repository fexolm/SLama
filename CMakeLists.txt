cmake_minimum_required(VERSION 2.8)
project(SLama)

set(CMAKE_C_STANDARD 11)
set (CMAKE_SHARED_LINKER_FLAGS "-Wl,-fsanitize=address -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -std=c11 -Werror -fsanitize=address -fprofile-arcs -ftest-coverage")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

file(GLOB SOURCE_FILES src/*)

add_subdirectory(tests)
add_subdirectory(libs/Testy)

add_library(SLama ${SOURCE_FILES})

