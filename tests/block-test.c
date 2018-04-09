/*!
 * @author fexolm 
 * @date 05.04.18.
 */

#include <stdint.h>
#include <stdlib.h>
#include <block.h>
#include <Testy/testy.h>
#include <Testy/assert.h>

TESTY_CASE (block_alloc_test) {
  SL_b_Block *block = SL_b_alloc(sizeof(int)*10);
  int *arr = block->mem;
  for (int i = 0; i < block->len/sizeof(int); i++) {
    arr[i] = i + 2;
  }
  for (int i = 9; i >= 0; i--) {
    testy_assert_int_eq(arr[i], i + 2);
  }
  SL_b_destroy(block);
}

TESTY_CASE (block_link_test) {
  SL_b_Block *block = SL_b_alloc(sizeof(int)*10);

  SL_b_Block *block2 = SL_b_share(block);

  int *arr = block->mem;
  for (int i = 0; i < block->len/sizeof(int); i++) {
    arr[i] = i + 2;
  }
  SL_b_destroy(block);

  arr = block2->mem;

  for (int i = 9; i >= 0; i--) {
    testy_assert_int_eq(arr[i], i + 2);
  }
  SL_b_destroy(block2);
}

TESTY_CASE (block_copy_test) {
  SL_b_Block *block = SL_b_alloc(sizeof(int)*10);

  int *arr = block->mem;
  for (int i = 0; i < block->len/sizeof(int); i++) {
    arr[i] = i + 2;
  }
  SL_b_Block *block2 = SL_b_copy(block);

  SL_b_destroy(block);

  arr = block2->mem;

  for (int i = 9; i >= 0; i--) {
    testy_assert_int_eq(arr[i], i + 2);
  }

  SL_b_destroy(block2);
}

TESTY_CASE (block_swap_test) {
  SL_b_Block *block = SL_b_alloc(sizeof(int)*10);
  SL_b_Block *block2 = SL_b_alloc(sizeof(int)*10);

  int *arr = block->mem;
  for (int i = 0; i < block->len/sizeof(int); i++) {
    arr[i] = i + 2;
  }
  arr = block2->mem;
  for (int i = 0; i < block->len/sizeof(int); i++) {
    arr[i] = i - 2;
  }

  SL_b_swap(block, block2);

  arr = block2->mem;
  for (int i = 9; i >= 0; i--) {
    testy_assert_int_eq(arr[i], i + 2);
  }
  arr = block->mem;
  for (int i = 9; i >= 0; i--) {
    testy_assert_int_eq(arr[i], i - 2);
  }
  SL_b_destroy(block);
  SL_b_destroy(block2);
}


int main() {
  testy_Runner runner = testy_allocRunner();
  testy_addCase(runner, block_alloc_test);
  testy_addCase(runner, block_alloc_test);
  testy_addCase(runner, block_copy_test);
  testy_addCase(runner, block_swap_test);
  testy_addCase(runner, block_link_test);
  testy_run(runner);
  testy_destoyRunner(runner);
  return 0;
}