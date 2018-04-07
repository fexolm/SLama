/*!
 * @author fexolm
 * @date 05.04.18.
 */

#include <libzvbi.h>
#include "matrix.h"
#include <stdlib.h>
#include <memory.h>
#include <assert.h>
__SL_m_Block *__SL_m_allocBlock(size_t len) {
  static const size_t block_size = sizeof(__SL_m_Block);
  void *mem = malloc(block_size + len);
  __SL_m_Block *block = mem;
  block->mem = mem + block_size;
  block->len = len;
  block->links = 1;
  return block;
}
void __SL_m_destroyBlock(__SL_m_Block *block) {
  assert(block->links && "Attempt to free empty block");
  if (!(--block->links)) {
    free(block);
  }
}
__SL_m_Block *__SL_m_addLink(__SL_m_Block *block) {
  block->links++;
  return block;
}
__SL_m_Block *__SL_m_copyBlock(const __SL_m_Block *const block) {
  __SL_m_Block *res = __SL_m_allocBlock(block->len);
  memcpy(res->mem, block->mem, block->len);
  res->len = 1;
  return res;
}
void __SL_m_swapBlocks(__SL_m_Block *lhs, __SL_m_Block *rhs) {
  assert(lhs->len==rhs->len && "Blocks should have same size");
  void *tmp = malloc(lhs->len);
  memcpy(tmp, lhs->mem, lhs->len);
  memcpy(lhs->mem, rhs->mem, lhs->len);
  memcpy(rhs->mem, tmp, lhs->len);
  free(tmp);
}
__SL_m_Matrix *__SL_m_allocMatrix_double(size_t width, size_t height) {
  __SL_m_Matrix *result = malloc(sizeof(__SL_m_Matrix));
  result->block_height = height;
  result->block_width = width;
  result->width = width;
  result->height = height;
  result->offsetX = 0;
  result->offsetY = 0;
  result->transpose = false;
  result->block = __SL_m_allocBlock(width*height*sizeof(double));
  return result;
}
void __SL_m_destroyMatrix(__SL_m_Matrix *matrix) {
  __SL_m_destroyBlock(matrix->block);
  free(matrix);
}
static inline __SL_m_Matrix *__copyMatrixBody(__SL_m_Matrix *matrix) {
  __SL_m_Matrix *result = malloc(sizeof(__SL_m_Matrix));
  result->transpose = matrix->transpose;
  result->offsetX = matrix->offsetX;
  result->offsetY = matrix->offsetY;
  result->width = matrix->width;
  result->height = matrix->height;
  result->block_height = matrix->block_height;
  result->block_width = matrix->block_width;
  return result;
}
__SL_m_Matrix *__SL_m_shareMatrix(__SL_m_Matrix *matrix) {
  __SL_m_Matrix *result = __copyMatrixBody(matrix);
  result->block = __SL_m_addLink(matrix->block);
  return result;
}
__SL_m_Matrix *__SL_m_copyMatrix(__SL_m_Matrix *matrix) {
  __SL_m_Matrix *result = __copyMatrixBody(matrix);
  result->block = __SL_m_copyBlock(matrix->block);
  return result;
}
double __SL_m_getMatrixElement_double(__SL_m_Matrix *matrix, int x, int y) {
  double *mem = matrix->block->mem;
  if (matrix->transpose) {
    return mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*y + x];
  } else {
    return mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*x + y];
  }
}
void __SL_m_setMatrixElement_double(__SL_m_Matrix *matrix, int x, int y, double value) {
  double *mem = matrix->block->mem;
  if (matrix->transpose) {
    mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*y + x] = value;
  } else {
    mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*x + y] = value;
  }
}
void __SL_m_transposeMatrix(__SL_m_Matrix *matrix) {
  matrix->transpose = !matrix->transpose;
  size_t tmp = matrix->height;
  matrix->height = matrix->width;
  matrix->width = tmp;
}


