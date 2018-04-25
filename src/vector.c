/*!
 * @author fexolm
 * @date 16.04.18.
 */
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "vector.h"
#include "matrix_core.h"
#include "block.h"

static inline void __checkLimits(SL_v_Vector *vector, size_t size) {
  assert(size >= 0 && size < vector->size && "Size out of range");
}

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
  __checkLimits(vector, ind);
  double *mem = vector->block->mem;
  return mem[ind + vector->offset];
}

void SL_v_setElementDouble(SL_v_Vector *vector, size_t ind, double value) {
  __checkLimits(vector, ind);
  double *mem = vector->block->mem;
  mem[ind + vector->offset] = value;
}

void SL_v_addToElementDouble(SL_v_Vector *vector, size_t ind, double value) {
  __checkLimits(vector, ind);
  double *mem = vector->block->mem;
  mem[ind + vector->offset] += value;
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
void SL_v_addDouble(SL_v_Vector *lhs, SL_v_Vector *rhs) {
  assert(lhs->size==rhs->size);
  for (size_t i = 0; i < lhs->size; i++) {
    SL_v_addToElementDouble(lhs, i, SL_v_getElementDouble(rhs, i));
  }
}
SL_v_Vector *SL_v_sumDouble(SL_v_Vector *lhs, SL_v_Vector *rhs) {
  SL_v_Vector *result = SL_v_fullCopy(lhs);
  SL_v_addDouble(result, rhs);
  return result;
}
void SL_v_substractDouble(SL_v_Vector *lhs, SL_v_Vector *rhs) {
  assert(lhs->size==rhs->size);
  for (size_t i = 0; i < lhs->size; i++) {
    SL_v_addToElementDouble(lhs, i, -SL_v_getElementDouble(rhs, i));
  }
}
SL_v_Vector *SL_v_diffDouble(SL_v_Vector *lhs, SL_v_Vector *rhs) {
  SL_v_Vector *result = SL_v_fullCopy(lhs);
  SL_v_substractDouble(result, rhs);
  return result;
}
double SL_v_dotDouble(SL_v_Vector *lhs, SL_v_Vector *rhs) {
	assert(lhs->size==rhs->size);
	double res = 0;
	double *lmem = lhs->block->mem;
	double *rmem = rhs->block->mem;
	for(int i = 0; i < lhs->size; i++) {
		res += lmem[i] * rmem[i];
	}
	return res;	
}
SL_m_Matrix *SL_v_toMatrix(SL_v_Vector *vector) {
	SL_m_Matrix *matrix = malloc(sizeof(SL_m_Matrix));
	matrix->block = SL_b_share(vector->block);
	matrix->block_width = 1;
	matrix->block_height = matrix->block->len;
	matrix->height = vector->size;
	matrix->width = 1;
	matrix->offsetX = 0;
	matrix->offsetY = vector->offset;
	matrix->transpose = false;
	return matrix;
}
