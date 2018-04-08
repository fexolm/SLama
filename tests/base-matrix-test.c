/*!
 * @author fexolm 
 * @date 07.04.18.
 */

#include <check.h>
#include <matrix_core.h>
#include <stdlib.h>
#include "test_utils.h"

START_TEST (matrix_alloc_test)
  {
    SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

    fill_matrix(matrix);

    base_check_matrix(matrix);

    SL_m_destroy(matrix);
  }
END_TEST

START_TEST (matrix_copy_test)
  {
    SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

    fill_matrix(matrix);

    base_check_matrix(matrix);

    SL_m_Matrix *matrix1 = SL_m_fullCopy(matrix);
    SL_m_destroy(matrix);

    base_check_matrix(matrix1);

    SL_m_destroy(matrix1);

  }
END_TEST

START_TEST (matrix_share_test)
  {
    SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);
    SL_m_Matrix *matrix1 = SL_m_share(matrix);

    fill_matrix(matrix);

    base_check_matrix(matrix);

    SL_m_destroy(matrix);

    base_check_matrix(matrix1);

    SL_m_destroy(matrix1);
  }
END_TEST

START_TEST (matrix_transpose_test)
  {
    SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

    fill_matrix(matrix);

    SL_m_transpose(matrix);

    for (int x = 0; x < matrix->height; x++) {
      for (int y = 0; y < matrix->width; y++) {
        ck_assert_double_eq(SL_m_getElementDouble(matrix, y, x), func(x, y));
      }
    }

    SL_m_destroy(matrix);
  }
END_TEST

START_TEST (matrix_slice_test)
  {
    SL_m_Matrix *matrix = SL_m_allocDouble(10, 15);

    fill_matrix(matrix);

    SL_m_Matrix *matrix1 = SL_m_getSlice(matrix, 3, 2, 5, 7);
    SL_m_destroy(matrix);
    for (int x = 0; x < matrix1->width; x++) {
      for (int y = 0; y < matrix1->height; y++) {
        ck_assert_double_eq(SL_m_getElementDouble(matrix1, x, y), func(x + 3, y + 2));
      }
    }
    SL_m_transpose(matrix1);
    for (int x = 0; x < matrix1->height; x++) {
      for (int y = 0; y < matrix1->width; y++) {
        ck_assert_double_eq(SL_m_getElementDouble(matrix1, y, x), func(x + 3, y + 2));
      }
    }
    SL_m_Matrix *matrix2 = SL_m_copyDouble(matrix1);

    SL_m_destroy(matrix1);
    for (int x = 0; x < matrix2->height; x++) {
      for (int y = 0; y < matrix2->width; y++) {
        ck_assert_double_eq(SL_m_getElementDouble(matrix2, y, x), func(x + 3, y + 2));
      }
    }

    SL_m_destroy(matrix2);
  }
END_TEST

Suite *test_suite() {
  Suite *s = suite_create("Matrix");
  TCase *tcase = tcase_create("Core test");
  tcase_add_test(tcase, matrix_alloc_test);
  tcase_add_test(tcase, matrix_copy_test);
  tcase_add_test(tcase, matrix_share_test);
  tcase_add_test(tcase, matrix_transpose_test);
  tcase_add_test(tcase, matrix_slice_test);
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