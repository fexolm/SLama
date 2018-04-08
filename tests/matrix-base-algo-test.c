/*!
 * @author fexolm 
 * @date 08.04.18.
 */

#include <check.h>
#include <matrix_core.h>
#include <stdlib.h>
#include <matrix_algorithms.h>
#include "test_utils.h"
START_TEST (matrix_sum_test)
  {
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
        ck_assert_double_eq(SL_m_getElementDouble(matrix, x, y), x + y);
        ck_assert_double_eq(SL_m_getElementDouble(matrix2, x, y), x + y);

      }
    }

    SL_m_destroy(matrix);
    SL_m_destroy(matrix1);
    SL_m_destroy(matrix2);

  }
END_TEST

START_TEST (matrix_diff_test)
  {
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
        ck_assert_double_eq(SL_m_getElementDouble(matrix, x, y), x - y);
        ck_assert_double_eq(SL_m_getElementDouble(matrix2, x, y), x - y);

      }
    }

    SL_m_destroy(matrix);
    SL_m_destroy(matrix1);
    SL_m_destroy(matrix2);

  }
END_TEST

START_TEST (matrix_scale_test)
  {
    SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);
    fill_matrix(matrix);

    SL_m_multByDouble(matrix, 4.54);

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        ck_assert_double_eq(SL_m_getElementDouble(matrix, x, y), func(x, y)*4.54);
      }
    }
    SL_m_destroy(matrix);
  }
END_TEST

Suite *test_suite() {
  Suite *s = suite_create("Matrix");
  TCase *tcase = tcase_create("Algorithms test");
  tcase_add_test(tcase, matrix_sum_test);
  tcase_add_test(tcase, matrix_diff_test);
  tcase_add_test(tcase, matrix_scale_test);
  suite_add_tcase(s, tcase);
  return s;
}

int main() {
  Suite *s = test_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}