/*!
 * @author fexolm 
 * @date 05.04.18.
 */

#include <check.h>
#include <matrix.h>
#include <stdint.h>
#include <stdlib.h>
START_TEST (block_alloc_test)
  {
    __SL_m_Block *block = __SL_m_allocBlock(sizeof(int)*10);
    int *arr = block->mem;
    for (int i = 0; i < block->len/sizeof(int); i++) {
      arr[i] = i + 2;
    }
    for (int i = 9; i >= 0; i--) {
      ck_assert_int_eq(arr[i], i + 2);
    }
    __SL_m_destroyBlock(block);
  }
END_TEST

START_TEST (block_link_test)
  {
    __SL_m_Block *block = __SL_m_allocBlock(sizeof(int)*10);

    __SL_m_Block *block2 = __SL_m_addLink(block);

    int *arr = block->mem;
    for (int i = 0; i < block->len/sizeof(int); i++) {
      arr[i] = i + 2;
    }
    __SL_m_destroyBlock(block);

    arr = block2->mem;

    for (int i = 9; i >= 0; i--) {
      ck_assert_int_eq(arr[i], i + 2);
    }
    __SL_m_destroyBlock(block2);
  }
END_TEST

START_TEST (block_copy_test)
  {
    __SL_m_Block *block = __SL_m_allocBlock(sizeof(int)*10);

    int *arr = block->mem;
    for (int i = 0; i < block->len/sizeof(int); i++) {
      arr[i] = i + 2;
    }
    __SL_m_Block *block2 = __SL_m_copyBlock(block);

    __SL_m_destroyBlock(block);

    arr = block2->mem;

    for (int i = 9; i >= 0; i--) {
      ck_assert_int_eq(arr[i], i + 2);
    }

    __SL_m_destroyBlock(block2);
  }
END_TEST

START_TEST (block_swap_test)
  {
    __SL_m_Block *block = __SL_m_allocBlock(sizeof(int)*10);
    __SL_m_Block *block2 = __SL_m_allocBlock(sizeof(int)*10);

    int *arr = block->mem;
    for (int i = 0; i < block->len/sizeof(int); i++) {
      arr[i] = i + 2;
    }
    arr = block2->mem;
    for (int i = 0; i < block->len/sizeof(int); i++) {
      arr[i] = i - 2;
    }

    __SL_m_swapBlocks(block, block2);

    arr = block2->mem;
    for (int i = 9; i >= 0; i--) {
      ck_assert_int_eq(arr[i], i + 2);
    }
    arr = block->mem;
    for (int i = 9; i >= 0; i--) {
      ck_assert_int_eq(arr[i], i - 2);
    }
    __SL_m_destroyBlock(block2);
  }
END_TEST

Suite *block_test_suite() {
  Suite *s = suite_create("Block");
  TCase *tcase = tcase_create("Alloc test");
  tcase_add_test(tcase, block_alloc_test);
  tcase_add_test(tcase, block_alloc_test);
  tcase_add_test(tcase, block_copy_test);
  tcase_add_test(tcase, block_swap_test);
  suite_add_tcase(s, tcase);

  return s;
}

int main() {
  Suite *s = block_test_suite();
  SRunner *sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return failed ? EXIT_FAILURE : EXIT_SUCCESS;
}