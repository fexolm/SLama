cmake_minimum_required(VERSION 2.8)
project(SLama-tests)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ../cmake)

enable_testing()

find_package(Check)

message(CHECK STATUS ${Check_LIBRARIES})

set (CMAKE_SHARED_LINKER_FLAGS "-Wl,-fsanitize=address -fprofile-arcs -ftest-coverage -pthread -lcheck_pic -pthread -lrt -lm -lsubunit")
set(CMAKE_C_FLAGS "-g -O0 -Wall -std=c11 -Werror -fsanitize=address -fprofile-arcs -ftest-coverage")

find_package(Threads REQUIRED)

add_executable(block_test test_utils.h block-test.c)
target_link_libraries(block_test SLama ${Check_LIBRARIES} pthread)
include_directories(../src/)
add_test(block_test block_test)

add_executable(base_matrix_test test_utils.h base-matrix-test.c)
target_link_libraries(base_matrix_test SLama ${Check_LIBRARIES} m pthread)
include_directories(../src/)
add_test(base_matrix_test base_matrix_test)

add_executable(matrix_base_algo_test test_utils.h matrix-base-algo-test.c)
target_link_libraries(matrix_base_algo_test SLama ${Check_LIBRARIES} m pthread)
include_directories(../src/)
add_test(matrix_base_algo_test matrix_base_algo_test)

add_executable(matmul_test test_utils.h matmul-test.c)
target_link_libraries(matmul_test SLama ${Check_LIBRARIES} m pthread)
include_directories(../src/)
add_test(matmul_test matmul_test)
