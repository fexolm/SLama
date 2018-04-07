/*!
 * @author fexolm 
 * @date 07.04.18.
 */

#include <check.h>
#include <matrix.h>
#include <stdint.h>
#include <stdlib.h>
START_TEST (matrix_alloc_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocMatrix_double(10, 10);

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        __SL_m_setMatrixElement_double(matrix, x, y, x - y);
      }
    }

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        ck_assert_int_eq(__SL_m_getMatrixElement_double(matrix, x, y), x - y);
      }
    }

    __SL_m_destroyMatrix(matrix);
  }
END_TEST

START_TEST (matrix_copy_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocMatrix_double(10, 10);

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        __SL_m_setMatrixElement_double(matrix, x, y, x - y);
      }
    }

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        ck_assert_int_eq(__SL_m_getMatrixElement_double(matrix, x, y), x - y);
      }
    }

    __SL_m_Matrix *matrix1 = __SL_m_copyMatrix(matrix);
    __SL_m_destroyMatrix(matrix);

    for (int x = 0; x < matrix1->width; x++) {
      for (int y = 0; y < matrix1->height; y++) {
        ck_assert_int_eq(__SL_m_getMatrixElement_double(matrix1, x, y), x - y);
      }
    }
    __SL_m_destroyMatrix(matrix1);

  }
END_TEST

START_TEST (matrix_share_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocMatrix_double(10, 10);
    __SL_m_Matrix *matrix1 = __SL_m_shareMatrix(matrix);

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        __SL_m_setMatrixElement_double(matrix, x, y, x - y);
      }
    }

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        ck_assert_int_eq(__SL_m_getMatrixElement_double(matrix, x, y), x - y);
      }
    }

    __SL_m_destroyMatrix(matrix);

    for (int x = 0; x < matrix1->width; x++) {
      for (int y = 0; y < matrix1->height; y++) {
        ck_assert_int_eq(__SL_m_getMatrixElement_double(matrix1, x, y), x - y);
      }
    }
    __SL_m_destroyMatrix(matrix1);
  }
END_TEST

START_TEST (matrix_transpose_test)
  {
    __SL_m_Matrix *matrix = __SL_m_allocMatrix_double(10, 10);

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        __SL_m_setMatrixElement_double(matrix, x, y, x - y);
      }
    }

    __SL_m_transposeMatrix(matrix);

    for (int x = 0; x < matrix->width; x++) {
      for (int y = 0; y < matrix->height; y++) {
        ck_assert_int_eq(__SL_m_getMatrixElement_double(matrix, y, x), x - y);
      }
    }

    __SL_m_destroyMatrix(matrix);
  }
END_TEST

Suite *test_suite() {
  Suite *s = suite_create("Matrix");
  TCase *tcase = tcase_create("Alloc test");
  tcase_add_test(tcase, matrix_alloc_test);
  tcase_add_test(tcase, matrix_copy_test);
  tcase_add_test(tcase, matrix_share_test);
  tcase_add_test(tcase, matrix_transpose_test);

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