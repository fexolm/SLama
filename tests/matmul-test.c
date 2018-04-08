/*!
 * @author fexolm 
 * @date 08.04.18.
 */
#include <check.h>
#include <matrix_core.h>
#include <stdlib.h>
#include <matrix_algorithms.h>

START_TEST (matmul_test1)
  {
    SL_m_Matrix *matrix1 = SL_m_allocDouble(4, 3);
    SL_m_Matrix *matrix2 = SL_m_allocDouble(5, 4);

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

    SL_m_Matrix *result = SL_m_matmulDouble(matrix1, matrix2);

    ck_assert_double_eq(SL_m_getElementDouble(result, 0, 0), 5523);
    ck_assert_double_eq(SL_m_getElementDouble(result, 1, 0), 4224);
    ck_assert_double_eq(SL_m_getElementDouble(result, 2, 0), 7266);
    ck_assert_double_eq(SL_m_getElementDouble(result, 3, 0), 5016);
    ck_assert_double_eq(SL_m_getElementDouble(result, 4, 0), 2735);
    ck_assert_double_eq(SL_m_getElementDouble(result, 0, 1), 8630);
    ck_assert_double_eq(SL_m_getElementDouble(result, 1, 1), 6626);
    ck_assert_double_eq(SL_m_getElementDouble(result, 2, 1), 11475);
    ck_assert_double_eq(SL_m_getElementDouble(result, 3, 1), 7609);
    ck_assert_double_eq(SL_m_getElementDouble(result, 4, 1), 4754);
    ck_assert_double_eq(SL_m_getElementDouble(result, 0, 2), 4312);
    ck_assert_double_eq(SL_m_getElementDouble(result, 1, 2), 4536);
    ck_assert_double_eq(SL_m_getElementDouble(result, 2, 2), 7110);
    ck_assert_double_eq(SL_m_getElementDouble(result, 3, 2), 4454);
    ck_assert_double_eq(SL_m_getElementDouble(result, 4, 2), 3869);

    SL_m_destroy(matrix1);
    SL_m_destroy(matrix2);
    SL_m_destroy(result);
  }
END_TEST

Suite *test_suite() {
  Suite *s = suite_create("Matrix");
  TCase *tcase = tcase_create("Matmul test");
  tcase_add_test(tcase, matmul_test1);
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