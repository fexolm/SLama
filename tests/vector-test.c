/*!
 * @author fexolm 
 * @date 16.04.18.
 */

#include <vector.h>
#include <Testy/assert.h>
#include <Testy/testy.h>

TESTY_INIT

TESTY_CASE(vector_alloc_test)
  SL_v_Vector *v = NULL;
  v = SL_v_allocDouble(10);
  for (int i = 0; i < 10; i++) {
    SL_v_setElementDouble(v, i, i + 2);
  }

  for (int i = 0; i < 10; i++) {
    testy_assert_double_eq(i + 2, SL_v_getElementDouble(v, i));
  }
TESTY_CLEANUP
  if (v)
    SL_v_destroy(v);
END_CASE

TESTY_CASE(vector_slice_test)
  SL_v_Vector *v = NULL;
  SL_v_Vector *v2 = NULL;
  v = SL_v_allocDouble(10);
  for (int i = 0; i < 10; i++) {
    SL_v_setElementDouble(v, i, i + 2);
  }
  v2 = SL_v_slice(v, 2, 4);

  for (int i = 0; i < 4; i++) {
    testy_assert_double_eq(i + 4, SL_v_getElementDouble(v2, i));
  }
TESTY_CLEANUP
  if (v)
    SL_v_destroy(v);
  if (v2)
    SL_v_destroy(v2);
END_CASE

TESTY_CASE(vector_share_test)
  SL_v_Vector *v = NULL;
  SL_v_Vector *v2 = NULL;
  v = SL_v_allocDouble(10);
  for (int i = 0; i < 10; i++) {
    SL_v_setElementDouble(v, i, i + 2);
  }
  v2 = SL_v_share(v);

  for (int i = 0; i < 10; i++) {
    testy_assert_double_eq(i + 2, SL_v_getElementDouble(v2, i));
  }
TESTY_CLEANUP
  if (v)
    SL_v_destroy(v);
  if (v2)
    SL_v_destroy(v2);
END_CASE

TESTY_CASE(vector_copy_test)
  SL_v_Vector *v = NULL;
  SL_v_Vector *v2 = NULL;
  v = SL_v_allocDouble(10);
  for (int i = 0; i < 10; i++) {
    SL_v_setElementDouble(v, i, i + 2);
  }
  v2 = SL_v_fullCopy(v);

  for (int i = 0; i < 10; i++) {
    testy_assert_double_eq(i + 2, SL_v_getElementDouble(v2, i));
  }
TESTY_CLEANUP
  if (v)
    SL_v_destroy(v);
  if (v2)
    SL_v_destroy(v2);
END_CASE

TESTY_CASE(vector_copy_test2)
  SL_v_Vector *v = NULL;
  SL_v_Vector *v2 = NULL;
  SL_v_Vector *v3 = NULL;

  v = SL_v_allocDouble(10);
  for (int i = 0; i < 10; i++) {
    SL_v_setElementDouble(v, i, i + 2);
  }
  v2 = SL_v_slice(v, 2, 4);

  v3 = SL_v_copyDouble(v2);

  testy_assert_int_eq(v3->size, 4);
  testy_assert_int_eq(v3->offset, 0);

  for (int i = 0; i < 4; i++) {
    testy_assert_double_eq(i + 4, SL_v_getElementDouble(v3, i));
  }
TESTY_CLEANUP
  if (v)
    SL_v_destroy(v);
  if (v2)
    SL_v_destroy(v2);
  if (v3)
    SL_v_destroy(v3);
END_CASE

TESTY_CASE(vector_sum_test)
  SL_v_Vector *v = NULL;
  SL_v_Vector *v2 = NULL;
  SL_v_Vector *res = NULL;
  SL_v_Vector *res2 = NULL;

  v = SL_v_allocDouble(15);
  v2 = SL_v_allocDouble(15);

  for (size_t i = 0; i < v->size; i++) {
    SL_v_setElementDouble(v, i, i*4);
    SL_v_setElementDouble(v2, i, i*14);
  }

  res = SL_v_sumDouble(v, v2);
  res2 = SL_v_diffDouble(v2, v);
  for (size_t i = 0; i < v->size; i++) {
    testy_assert_double_eq(SL_v_getElementDouble(res, i), i*18);
    testy_assert_double_eq(SL_v_getElementDouble(res2, i), i*10);
  }

TESTY_CLEANUP
  if (v)
    SL_v_destroy(v);
  if (v2)
    SL_v_destroy(v2);
  if (res) {
    SL_v_destroy(res);
  }
  if (res2) {
    SL_v_destroy(res2);
  }
END_CASE

int main() {
  testy_Runner runner = testy_allocRunner();
  testy_addCase(runner, vector_alloc_test);
  testy_addCase(runner, vector_share_test);
  testy_addCase(runner, vector_slice_test);
  testy_addCase(runner, vector_copy_test);
  testy_addCase(runner, vector_sum_test);
  testy_run(runner);
  int errors = testy_errorCount(runner);
  testy_destroyRunner(runner);
  return errors ? EXIT_FAILURE : EXIT_SUCCESS;
}
