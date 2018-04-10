/*!
 * @author fexolm 
 * @date 07.04.18.
 */

#include <matrix_core.h>
#include <stdlib.h>
#include "test_utils.h"
#include <Testy/testy.h>
#include <Testy/assert.h>

TESTY_INIT

TESTY_CASE (matrix_alloc_test)
  SL_m_Matrix *matrix = NULL;
  matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  base_check_matrix(matrix);
TEASTY_CLEANUP
  if (matrix)
    SL_m_destroy(matrix);
END_CASE

TESTY_CASE (matrix_copy_test)
  SL_m_Matrix *matrix = NULL;
  SL_m_Matrix *matrix1 = NULL;
  matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  base_check_matrix(matrix);

  matrix1 = SL_m_fullCopy(matrix);

  base_check_matrix(matrix1);
TEASTY_CLEANUP
  if (matrix)
    SL_m_destroy(matrix);
  if (matrix1)
    SL_m_destroy(matrix1);
END_CASE

TESTY_CASE (matrix_share_test)
  SL_m_Matrix *matrix = NULL;
  SL_m_Matrix *matrix1 = NULL;
  matrix = SL_m_allocDouble(10, 15);
  matrix1 = SL_m_share(matrix);

  fill_matrix(matrix);

  base_check_matrix(matrix);

  base_check_matrix(matrix1);

TEASTY_CLEANUP
  if (matrix)
    SL_m_destroy(matrix);
  if (matrix1)
    SL_m_destroy(matrix1);
END_CASE

TESTY_CASE (matrix_transpose_test)
  SL_m_Matrix *matrix = NULL;
  matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  SL_m_transpose(matrix);

  for (int x = 0; x < matrix->height; x++) {
    for (int y = 0; y < matrix->width; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix, y, x), func(x, y));
    }
  }
TEASTY_CLEANUP
  if (matrix)
    SL_m_destroy(matrix);
END_CASE

TESTY_CASE (matrix_slice_test)
  SL_m_Matrix *matrix = NULL;
  SL_m_Matrix *matrix1 = NULL;
  SL_m_Matrix *matrix2 = NULL;
  matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  matrix1 = SL_m_getSlice(matrix, 3, 2, 5, 7);
  for (int x = 0; x < matrix1->width; x++) {
    for (int y = 0; y < matrix1->height; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix1, x, y), func(x + 3, y + 2));
    }
  }
  SL_m_transpose(matrix1);
  for (int x = 0; x < matrix1->height; x++) {
    for (int y = 0; y < matrix1->width; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix1, y, x), func(x + 3, y + 2));
    }
  }
  matrix2 = SL_m_copyDouble(matrix1);

  for (int x = 0; x < matrix2->height; x++) {
    for (int y = 0; y < matrix2->width; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix2, y, x), func(x + 3, y + 2));
    }
  }
TEASTY_CLEANUP
  if (matrix)
    SL_m_destroy(matrix);
  if (matrix1)
    SL_m_destroy(matrix1);
  if (matrix2)
    SL_m_destroy(matrix2);
END_CASE

int main() {
  testy_Runner runner = testy_allocRunner();
  testy_addCase(runner, matrix_alloc_test);
  testy_addCase(runner, matrix_copy_test);
  testy_addCase(runner, matrix_share_test);
  testy_addCase(runner, matrix_transpose_test);
  testy_addCase(runner, matrix_slice_test);
  testy_run(runner);
  int errors = testy_errorCount(runner);
  testy_destroyRunner(runner);
  return errors ? EXIT_FAILURE:EXIT_SUCCESS;
}