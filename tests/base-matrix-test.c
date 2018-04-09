/*!
 * @author fexolm 
 * @date 07.04.18.
 */

#include <matrix_core.h>
#include <stdlib.h>
#include "test_utils.h"
#include <Testy/testy.h>
#include <Testy/assert.h>

TESTY_CASE (matrix_alloc_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  base_check_matrix(matrix);

  SL_m_destroy(matrix);
}

TESTY_CASE (matrix_copy_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  base_check_matrix(matrix);

  SL_m_Matrix *matrix1 = SL_m_fullCopy(matrix);
  SL_m_destroy(matrix);

  base_check_matrix(matrix1);

  SL_m_destroy(matrix1);

}

TESTY_CASE (matrix_share_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);
  SL_m_Matrix *matrix1 = SL_m_share(matrix);

  fill_matrix(matrix);

  base_check_matrix(matrix);

  SL_m_destroy(matrix);

  base_check_matrix(matrix1);

  SL_m_destroy(matrix1);
}

TESTY_CASE (matrix_transpose_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  SL_m_transpose(matrix);

  for (int x = 0; x < matrix->height; x++) {
    for (int y = 0; y < matrix->width; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix, y, x), func(x, y));
    }
  }
  SL_m_destroy(matrix);
}

TESTY_CASE (matrix_slice_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

  fill_matrix(matrix);

  SL_m_Matrix *matrix1 = SL_m_getSlice(matrix, 3, 2, 5, 7);
  SL_m_destroy(matrix);
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
  SL_m_Matrix *matrix2 = SL_m_copyDouble(matrix1);

  SL_m_destroy(matrix1);
  for (int x = 0; x < matrix2->height; x++) {
    for (int y = 0; y < matrix2->width; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix2, y, x), func(x + 3, y + 2));
    }
  }

  SL_m_destroy(matrix2);
}

int main() {
  testy_Runner runner = testy_allocRunner();
  testy_addCase(runner, matrix_alloc_test);
  testy_addCase(runner, matrix_copy_test);
  testy_addCase(runner, matrix_share_test);
  testy_addCase(runner, matrix_transpose_test);
  testy_addCase(runner, matrix_slice_test);
  testy_run(runner);
  testy_destoyRunner(runner);
  return 0;
}