/*!
 * @author fexolm 
 * @date 07.04.18.
 */

#include <check.h>
#include <matrix_core.h>
#include <stdlib.h>
#include <stdio.h>
double func(double x, double y) {
  return 6*sin(x) - y*y;
}

void fill_matrix(__SL_m_Matrix *matrix) {
  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      __SL_m_setElementDouble(matrix, x, y, func(x, y));
    }
  }
}

void print_matrix(__SL_m_Matrix *matrix) {
  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      printf("%f ", __SL_m_getElementDouble_(matrix, x, y));
    }
    printf("\n");
  }
  printf("\n");
}

void base_check_matrix(__SL_m_Matrix *matrix) {
  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      ck_assert_double_eq(__SL_m_getElementDouble_(matrix, x, y), func(x, y));
    }
  }
}

START_TEST (matrix_alloc_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocDouble(10, 10);

    fill_matrix(matrix);

    base_check_matrix(matrix);

    __SL_m_destroy(matrix);
  }
END_TEST

START_TEST (matrix_copy_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocDouble(10, 10);

    fill_matrix(matrix);

    base_check_matrix(matrix);

    __SL_m_Matrix *matrix1 = __SL_m_fullCopy(matrix);
    __SL_m_destroy(matrix);

    base_check_matrix(matrix1);

    __SL_m_destroy(matrix1);

  }
END_TEST

START_TEST (matrix_share_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocDouble(10, 10);
    __SL_m_Matrix *matrix1 = __SL_m_share(matrix);

    fill_matrix(matrix);

    base_check_matrix(matrix);

    __SL_m_destroy(matrix);

    base_check_matrix(matrix1);

    __SL_m_destroy(matrix1);
  }
END_TEST

START_TEST (matrix_transpose_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocDouble(10, 10);

    fill_matrix(matrix);

    __SL_m_transpose(matrix);

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        ck_assert_double_eq(__SL_m_getElementDouble_(matrix, y, x), func(x, y));
      }
    }

    __SL_m_destroy(matrix);
  }
END_TEST

START_TEST (matrix_slice_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocDouble(10, 10);

    fill_matrix(matrix);

    __SL_m_Matrix *matrix1 = __SL_m_getSlice(matrix, 3, 2, 5, 5);
    __SL_m_destroy(matrix);
    for (int x = 0; x < matrix1->width; x++) {
      for (int y = 0; y < matrix1->height; y++) {
        ck_assert_double_eq(__SL_m_getElementDouble_(matrix1, x, y), func(x + 3, y + 2));
      }
    }
    __SL_m_transpose(matrix1);
    for (int x = 0; x < matrix1->width; x++) {
      for (int y = 0; y < matrix1->height; y++) {
        ck_assert_double_eq(__SL_m_getElementDouble_(matrix1, y, x), func(x + 3, y + 2));
      }
    }
    __SL_m_Matrix *matrix2 = __SL_m_copyDouble(matrix1);

    __SL_m_destroy(matrix1);
    for (int x = 0; x < matrix2->width; x++) {
      for (int y = 0; y < matrix2->height; y++) {
        ck_assert_double_eq(__SL_m_getElementDouble_(matrix2, y, x), func(x + 3, y + 2));
      }
    }

    __SL_m_destroy(matrix2);
  }
END_TEST

Suite *test_suite() {
  Suite *s = suite_create("Matrix");
  TCase *tcase = tcase_create("Alloc test");
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