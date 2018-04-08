/*!
 * @author fexolm 
 * @date 08.04.18.
 */
#include "block.h"
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
__SL_b_Block *__SL_b_alloc(size_t len) {
  static const size_t block_size = sizeof(__SL_b_Block);
  void *mem = malloc(block_size + len);
  __SL_b_Block *block = mem;
  block->mem = mem + block_size;
  block->len = len;
  block->links = 1;
  return block;
}
void __SL_b_destroy(__SL_b_Block *block) {
  assert(block->links && "Attempt to free empty block");
  if (!(--block->links)) {
    free(block);
  }
}
__SL_b_Block *__SL_b_share(__SL_b_Block *block) {
  block->links++;
  return block;
}
__SL_b_Block *__SL_b_copy(const __SL_b_Block *const block) {
  __SL_b_Block *res = __SL_b_alloc(block->len);
  memcpy(res->mem, block->mem, block->len);
  res->len = 1;
  return res;
}
void __SL_b_swap(__SL_b_Block *lhs, __SL_b_Block *rhs) {
  assert(lhs->len==rhs->len && "Blocks should have same size");
  void *tmp = malloc(lhs->len);
  memcpy(tmp, lhs->mem, lhs->len);
  memcpy(lhs->mem, rhs->mem, lhs->len);
  memcpy(rhs->mem, tmp, lhs->len);
  free(tmp);
}