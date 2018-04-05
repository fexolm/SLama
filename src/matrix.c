/*!
 * @author fexolm
 * @date 05.04.18.
 */

#include <libzvbi.h>
#include "matrix.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
__SL_m_block *__SL_m_allocBlock(size_t len) {
  static const size_t block_size = sizeof(__SL_m_block);
  void *mem = malloc(block_size + len);
  __SL_m_block *block = mem;
  block->mem = mem + block_size;
  block->len = len;
  block->links = 1;
  return block;
}
void __SL_m_destroyBlock(__SL_m_block *block) {
  assert(block->links && "Attempt to free empty block");
  if (!(--block->links)) {
    free(block);
  }
}
__SL_m_block *__SL_m_addLink(__SL_m_block *block) {
  block->links++;
  return block;
}
__SL_m_block *__SL_m_copyBlock(const __SL_m_block *const block) {
  __SL_m_block *res = __SL_m_allocBlock(block->len);
  memcpy(res->mem, block->mem, block->len);
  res->len = 1;
  return res;
}
void __SL_m_swapBlocks(__SL_m_block *lhs, __SL_m_block *rhs) {
  assert(lhs->len==rhs->len && "Blocks should have same size");
  void *tmp = malloc(lhs->len);
  memcpy(tmp, lhs->mem, lhs->len);
  memcpy(lhs->mem, rhs->mem, lhs->len);
  memcpy(rhs->mem, tmp, lhs->len);
  free(tmp);
}
