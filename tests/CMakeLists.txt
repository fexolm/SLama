cmake_minimum_required(VERSION 2.8)
project(SLama-tests)

set(CMAKE_C_STANDARD 11)
set(CMAKE_MODULE_PATH ../cmake)

enable_testing()

find_package(Check)

add_executable(block_test test_utils.h block-test.c)
target_link_libraries(block_test SLama ${Check_LIBRARIES})
include_directories(../src/)
add_test(block_test block_test)

add_executable(base_matrix_test test_utils.h base-matrix-test.c)
target_link_libraries(base_matrix_test SLama ${Check_LIBRARIES} m)
include_directories(../src/)
add_test(base_matrix_test base_matrix_test)

add_executable(matrix_base_algo_test test_utils.h matrix-base-algo-test.c)
target_link_libraries(matrix_base_algo_test SLama ${Check_LIBRARIES} m)
include_directories(../src/)
add_test(matrix_base_algo_test matrix_base_algo_test)

add_executable(matmul_test test_utils.h matmul-test.c)
target_link_libraries(matmul_test SLama ${Check_LIBRARIES} m)
include_directories(../src/)
add_test(matmul_test matmul_test)
