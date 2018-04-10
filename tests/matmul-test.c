/*!
 * @author fexolm 
 * @date 08.04.18.
 */

#include <matrix_core.h>
#include <stdlib.h>
#include <matrix_algorithms.h>
#include <Testy/testy.h>
#include <Testy/assert.h>

TESTY_INIT

TESTY_CASE (matmul_test1)
  SL_m_Matrix *matrix1 = NULL;
  SL_m_Matrix *matrix2 = NULL;
  SL_m_Matrix *result = NULL;

  matrix1 = SL_m_allocDouble(4, 3);
  matrix2 = SL_m_allocDouble(5, 4);

  SL_m_setElementDouble(matrix1, 0, 0, 42);
  SL_m_setElementDouble(matrix1, 1, 0, 23);
  SL_m_setElementDouble(matrix1, 2, 0, 34);
  SL_m_setElementDouble(matrix1, 3, 0, 64);
  SL_m_setElementDouble(matrix1, 0, 1, 73);
  SL_m_setElementDouble(matrix1, 1, 1, 45);
  SL_m_setElementDouble(matrix1, 2, 1, 53);
  SL_m_setElementDouble(matrix1, 3, 1, 87);
  SL_m_setElementDouble(matrix1, 0, 2, 45);
  SL_m_setElementDouble(matrix1, 1, 2, 75);
  SL_m_setElementDouble(matrix1, 2, 2, 8);
  SL_m_setElementDouble(matrix1, 3, 2, 35);

  SL_m_setElementDouble(matrix2, 0, 0, 56);
  SL_m_setElementDouble(matrix2, 1, 0, 34);
  SL_m_setElementDouble(matrix2, 2, 0, 45);
  SL_m_setElementDouble(matrix2, 3, 0, 2);
  SL_m_setElementDouble(matrix2, 4, 0, 44);
  SL_m_setElementDouble(matrix2, 0, 1, 5);
  SL_m_setElementDouble(matrix2, 1, 1, 24);
  SL_m_setElementDouble(matrix2, 2, 1, 42);
  SL_m_setElementDouble(matrix2, 3, 1, 34);
  SL_m_setElementDouble(matrix2, 4, 1, 23);
  SL_m_setElementDouble(matrix2, 0, 2, 24);
  SL_m_setElementDouble(matrix2, 1, 2, 2);
  SL_m_setElementDouble(matrix2, 2, 2, 45);
  SL_m_setElementDouble(matrix2, 3, 2, 43);
  SL_m_setElementDouble(matrix2, 4, 2, 3);
  SL_m_setElementDouble(matrix2, 0, 3, 35);
  SL_m_setElementDouble(matrix2, 1, 3, 34);
  SL_m_setElementDouble(matrix2, 2, 3, 45);
  SL_m_setElementDouble(matrix2, 3, 3, 42);
  SL_m_setElementDouble(matrix2, 4, 3, 4);

  result = SL_m_matmulDouble(matrix1, matrix2);

  testy_assert_double_eq(SL_m_getElementDouble(result, 0, 0), 5523);
  testy_assert_double_eq(SL_m_getElementDouble(result, 1, 0), 4224);
  testy_assert_double_eq(SL_m_getElementDouble(result, 2, 0), 7266);
  testy_assert_double_eq(SL_m_getElementDouble(result, 3, 0), 5016);
  testy_assert_double_eq(SL_m_getElementDouble(result, 4, 0), 2735);
  testy_assert_double_eq(SL_m_getElementDouble(result, 0, 1), 8630);
  testy_assert_double_eq(SL_m_getElementDouble(result, 1, 1), 6626);
  testy_assert_double_eq(SL_m_getElementDouble(result, 2, 1), 11475);
  testy_assert_double_eq(SL_m_getElementDouble(result, 3, 1), 7609);
  testy_assert_double_eq(SL_m_getElementDouble(result, 4, 1), 4754);
  testy_assert_double_eq(SL_m_getElementDouble(result, 0, 2), 4312);
  testy_assert_double_eq(SL_m_getElementDouble(result, 1, 2), 4536);
  testy_assert_double_eq(SL_m_getElementDouble(result, 2, 2), 7110);
  testy_assert_double_eq(SL_m_getElementDouble(result, 3, 2), 4454);
  testy_assert_double_eq(SL_m_getElementDouble(result, 4, 2), 3869);
TEASTY_CLEANUP
  if (matrix1)
    SL_m_destroy(matrix1);
  if (matrix2)
    SL_m_destroy(matrix2);
  if (result)
    SL_m_destroy(result);
END_CASE

int main() {
  testy_Runner runner = testy_allocRunner();
  testy_addCase(runner, matmul_test1);
  testy_run(runner);
  int errors = testy_errorCount(runner);
  testy_destroyRunner(runner);
  return errors ? EXIT_FAILURE:EXIT_SUCCESS;
}