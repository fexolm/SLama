/*!
 * @author fexolm 
 * @date 16.04.18.
 */
#include <stdlib.h>
#include "vector.h"

static inline SL_v_Vector *__buildVector(size_t size, SL_b_Block *block, size_t offset) {
  SL_v_Vector *result = malloc(sizeof(SL_v_Vector));
  result->size = size;
  result->block = block;
  result->offset = offset;
  return result;
}

SL_v_Vector *SL_v_allocDouble(size_t size) {
  return __buildVector(size, SL_b_alloc(sizeof(double)*size), 0);
}

void SL_v_destroy(SL_v_Vector *vector) {
  SL_b_destroy(vector->block);
  free(vector);
}

SL_v_Vector *SL_v_share(SL_v_Vector *vector) {
  return __buildVector(vector->size, SL_b_share(vector->block), vector->offset);
}

SL_v_Vector *SL_v_fullCopy(SL_v_Vector *vector) {
  return __buildVector(vector->size, SL_b_copy(vector->block), vector->offset);
}

double SL_v_getElementDouble(SL_v_Vector *vector, size_t ind) {
  double *mem = vector->block->mem;
  return mem[ind + vector->offset];
}

void SL_v_setElementDouble(SL_v_Vector *vector, size_t ind, double value) {
  double *mem = vector->block->mem;
  mem[ind + vector->offset] = value;
}

SL_v_Vector *SL_v_slice(SL_v_Vector *vector, int begin, size_t width) {
  return __buildVector(width, SL_b_share(vector->block), vector->offset + begin);
}

SL_v_Vector *SL_v_copyDouble(SL_v_Vector *vector) {
  SL_v_Vector *result = SL_v_allocDouble(vector->size);
  for (size_t i = 0; i < vector->size; i++) {
    SL_v_setElementDouble(result, i, SL_v_getElementDouble(vector, i));
  }
  return result;
}