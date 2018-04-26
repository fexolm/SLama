/*!
 * @author fexolm
 * @date 05.04.18.
 *
 * @todo add limits check
 */

#include "matrix_core.h"
#include <stdlib.h>
#include <assert.h>
#include "vector.h"

static inline void __checkLimits(SL_m_Matrix *matrix, int x, int y) {
  assert(x >= 0 && x < matrix->width && "X out of range");
  assert(y >= 0 && y < matrix->height && "Y out of range");
}

SL_m_Matrix *SL_m_allocDouble(size_t width, size_t height) {
  SL_m_Matrix *result = malloc(sizeof(SL_m_Matrix));
  result->block_width = width;
  result->width = width;
  result->height = height;
  result->offsetX = 0;
  result->offsetY = 0;
  result->transpose = false;
  result->block = SL_b_alloc(width*height*sizeof(double));
  return result;
}
void SL_m_destroy(SL_m_Matrix *matrix) {
  SL_b_destroy(matrix->block);
  free(matrix);
}
static inline SL_m_Matrix *__copyBody(SL_m_Matrix *matrix) {
  SL_m_Matrix *result = malloc(sizeof(SL_m_Matrix));
  result->transpose = matrix->transpose;
  result->offsetX = matrix->offsetX;
  result->offsetY = matrix->offsetY;
  result->width = matrix->width;
  result->height = matrix->height;
  result->block_width = matrix->block_width;
  return result;
}
SL_m_Matrix *SL_m_share(SL_m_Matrix *matrix) {
  SL_m_Matrix *result = __copyBody(matrix);
  result->block = SL_b_share(matrix->block);
  return result;
}
SL_m_Matrix *SL_m_fullCopy(SL_m_Matrix *matrix) {
  SL_m_Matrix *result = __copyBody(matrix);
  result->block = SL_b_copy(matrix->block);
  return result;
}
double SL_m_getElementDouble(SL_m_Matrix *matrix, int x, int y) {
  __checkLimits(matrix, x, y);
  double *mem = matrix->block->mem;
  if (!matrix->transpose) {
    return mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*y + x];
  } else {
    return mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*x + y];
  }
}
void SL_m_setElementDouble(SL_m_Matrix *matrix, int x, int y, double value) {
  __checkLimits(matrix, x, y);
  double *mem = matrix->block->mem;
  if (!matrix->transpose) {
    mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*y + x] = value;
  } else {
    mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*x + y] = value;
  }
}
void SL_m_transpose(SL_m_Matrix *matrix) {
  matrix->transpose = !matrix->transpose;
  size_t tmp = matrix->height;
  matrix->height = matrix->width;
  matrix->width = tmp;
}
SL_m_Matrix *SL_m_copyDouble(SL_m_Matrix *matrix) {
  SL_m_Matrix *result = SL_m_allocDouble(matrix->width, matrix->height);
  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      SL_m_setElementDouble(result, x, y, SL_m_getElementDouble(matrix, x, y));
    }
  }
  return result;
}
SL_m_Matrix *SL_m_slice(SL_m_Matrix *matrix, int xbegin, int ybegin, size_t width, size_t height) {
  __checkLimits(matrix, xbegin, ybegin);
  __checkLimits(matrix, (int) (xbegin + width), (int) (ybegin + height));
  SL_m_Matrix *result = SL_m_share(matrix);
  result->offsetX += xbegin;
  result->offsetY += ybegin;
  result->width = width;
  result->height = height;
  return result;
}

SL_v_Vector *SL_m_toVector(SL_m_Matrix *matrix) {
  assert(matrix->width==1);
  SL_v_Vector *res = malloc(sizeof(SL_v_Vector));
  res->block = SL_b_share(matrix->block);
  res->size = matrix->height;
  res->offset = matrix->offsetX + matrix->offsetY*matrix->block_width;
  res->shift = matrix->block_width;
  return res;
}


