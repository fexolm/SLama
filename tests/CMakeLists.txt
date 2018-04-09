cmake_minimum_required(VERSION 2.8)
project(SLama-tests)

set(CMAKE_C_STANDARD 11)

enable_testing()

set (CMAKE_SHARED_LINKER_FLAGS "-Wl,-fsanitize=address -fprofile-arcs -ftest-coverage ")
set(CMAKE_C_FLAGS "-g -O0 -Wall -std=c11 -Werror -fsanitize=address -fprofile-arcs -ftest-coverage")

find_package(Threads REQUIRED)

add_executable(block_test test_utils.h block-test.c)
target_link_libraries(block_test SLama testy)
include_directories(../src/ ../libs/Testy/include)
add_test(block_test block_test)

add_executable(base_matrix_test test_utils.h base-matrix-test.c)
target_link_libraries(base_matrix_test SLama m testy)
include_directories(../src/ ../libs/Testy/include)
add_test(base_matrix_test base_matrix_test)

add_executable(matrix_base_algo_test test_utils.h matrix-base-algo-test.c)
target_link_libraries(matrix_base_algo_test SLama m testy)
include_directories(../src/ ../libs/Testy/include)
add_test(matrix_base_algo_test matrix_base_algo_test)

add_executable(matmul_test test_utils.h matmul-test.c)
target_link_libraries(matmul_test SLama m testy)
include_directories(../src/ ../libs/Testy/include)
add_test(matmul_test matmul_test)
