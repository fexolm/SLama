/*!
 * @author fexolm 
 * @date 08.04.18.
 */

#include <matrix_core.h>
#include <stdlib.h>
#include <matrix_algorithms.h>
#include "test_utils.h"
#include <Testy/testy.h>
#include <Testy/assert.h>

TESTY_CASE (matrix_sum_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);
  SL_m_Matrix *matrix1 = SL_m_allocDouble(10, 15);

  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      SL_m_setElementDouble(matrix, x, y, x);
      SL_m_setElementDouble(matrix1, x, y, y);
    }
  }

  SL_m_Matrix *matrix2 = SL_m_sumDouble(matrix, matrix1);

  SL_m_addDouble(matrix, matrix1);

  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix, x, y), x + y);
      testy_assert_double_eq(SL_m_getElementDouble(matrix2, x, y), x + y);

    }
  }

  SL_m_destroy(matrix);
  SL_m_destroy(matrix1);
  SL_m_destroy(matrix2);

}

TESTY_CASE (matrix_diff_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);
  SL_m_Matrix *matrix1 = SL_m_allocDouble(10, 15);

  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      SL_m_setElementDouble(matrix, x, y, x);
      SL_m_setElementDouble(matrix1, x, y, y);
    }
  }

  SL_m_Matrix *matrix2 = SL_m_diffDouble(matrix, matrix1);

  SL_m_substractDouble(matrix, matrix1);

  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix, x, y), x - y);
      testy_assert_double_eq(SL_m_getElementDouble(matrix2, x, y), x - y);

    }
  }

  SL_m_destroy(matrix);
  SL_m_destroy(matrix1);
  SL_m_destroy(matrix2);

}

TESTY_CASE (matrix_scale_test) {
  SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);
  fill_matrix(matrix);

  SL_m_multByDouble(matrix, 4.54);

  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      testy_assert_double_eq(SL_m_getElementDouble(matrix, x, y), func(x, y)*4.54);
    }
  }
  SL_m_destroy(matrix);
}

int main() {
  testy_Runner runner = testy_allocRunner();
  testy_addCase(runner, matrix_sum_test);
  testy_addCase(runner, matrix_diff_test);
  testy_addCase(runner, matrix_scale_test);
  testy_run(runner);
  testy_destoyRunner(runner);
  return 0;
}