cmake_minimum_required(VERSION 3.10)
project(SLama-tests)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ../cmake)

enable_testing()

find_package(Check)

add_executable(block_test block-test.c)
target_link_libraries(block_test SLama ${Check_LIBRARIES})
include_directories(../src/)
add_test(block_test block_test)

add_executable(base_matrix_test base-matrix-test.c)
target_link_libraries(base_matrix_test SLama ${Check_LIBRARIES})
include_directories(../src/)
add_test(base_matrix_test base_matrix_test)
