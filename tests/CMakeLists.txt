cmake_minimum_required(VERSION 3.10)
project(SLama-tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ../cmake)

enable_testing()

find_package(Check)

add_executable(block_test block-test.c)
target_link_libraries(block_test SLama ${Check_LIBRARIES})
include_directories(../src/)

add_test(block-test block_test)
