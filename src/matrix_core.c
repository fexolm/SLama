/*!
 * @author fexolm
 * @date 05.04.18.
 *
 * @todo add limits check
 */

#include <libzvbi.h>
#include "matrix_core.h"
#include <stdlib.h>

__SL_m_Matrix *__SL_m_allocDouble(size_t width, size_t height) {
  __SL_m_Matrix *result = malloc(sizeof(__SL_m_Matrix));
  result->block_height = height;
  result->block_width = width;
  result->width = width;
  result->height = height;
  result->offsetX = 0;
  result->offsetY = 0;
  result->transpose = false;
  result->block = __SL_b_alloc(width*height*sizeof(double));
  return result;
}
void __SL_m_destroy(__SL_m_Matrix *matrix) {
  __SL_b_destroy(matrix->block);
  free(matrix);
}
static inline __SL_m_Matrix *__copyBody(__SL_m_Matrix *matrix) {
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
__SL_m_Matrix *__SL_m_share(__SL_m_Matrix *matrix) {
  __SL_m_Matrix *result = __copyBody(matrix);
  result->block = __SL_b_share(matrix->block);
  return result;
}
__SL_m_Matrix *__SL_m_fullCopy(__SL_m_Matrix *matrix) {
  __SL_m_Matrix *result = __copyBody(matrix);
  result->block = __SL_b_copy(matrix->block);
  return result;
}
double __SL_m_getElementDouble_(__SL_m_Matrix *matrix, int x, int y) {
  double *mem = matrix->block->mem;
  if (!matrix->transpose) {
    return mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*y + x];
  } else {
    return mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*x + y];
  }
}
void __SL_m_setElementDouble(__SL_m_Matrix *matrix, int x, int y, double value) {
  double *mem = matrix->block->mem;
  if (!matrix->transpose) {
    mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*y + x] = value;
  } else {
    mem[matrix->offsetY*matrix->block_width + matrix->offsetX + matrix->block_width*x + y] = value;
  }
}
void __SL_m_transpose(__SL_m_Matrix *matrix) {
  matrix->transpose = !matrix->transpose;
  size_t tmp = matrix->height;
  matrix->height = matrix->width;
  matrix->width = tmp;
}
__SL_m_Matrix *__SL_m_copyDouble(__SL_m_Matrix *matrix) {
  __SL_m_Matrix *result = __SL_m_allocDouble(matrix->width, matrix->height);
  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      __SL_m_setElementDouble(result, x, y, __SL_m_getElementDouble_(matrix, x, y));
    }
  }
  return result;
}
__SL_m_Matrix *__SL_m_getSlice(__SL_m_Matrix *matrix, int xbegin, int ybegin, size_t width, size_t height) {
  __SL_m_Matrix *result = __SL_m_share(matrix);
  result->offsetX += xbegin;
  result->offsetY += ybegin;
  result->width = width;
  result->height = height;
  return result;
}




