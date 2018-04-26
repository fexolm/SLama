/*!
 * @author fexolm 
 * @date 16.04.18.
 */
#pragma once

#include "block.h"

typedef struct __Matrix SL_m_Matrix;

typedef struct __Vector{
  SL_b_Block *block;
  size_t offset;
  size_t size;
  size_t shift;
} SL_v_Vector;

SL_v_Vector *SL_v_allocDouble(size_t size);

void SL_v_destroy(SL_v_Vector *vector);

SL_v_Vector *SL_v_share(SL_v_Vector *vector);

SL_v_Vector *SL_v_fullCopy(SL_v_Vector *vector);

double SL_v_getElementDouble(SL_v_Vector *vector, size_t ind);

void SL_v_setElementDouble(SL_v_Vector *vector, size_t ind, double value);

void SL_v_addToElementDouble(SL_v_Vector *vector, size_t ind, double value);

SL_v_Vector *SL_v_slice(SL_v_Vector *vector, int begin, size_t width);

SL_v_Vector *SL_v_copyDouble(SL_v_Vector *vector);

void SL_v_addDouble(SL_v_Vector *lhs, SL_v_Vector *rhs);

SL_v_Vector *SL_v_sumDouble(SL_v_Vector *lhs, SL_v_Vector *rhs);

void SL_v_substractDouble(SL_v_Vector *lhs, SL_v_Vector *rhs);

SL_v_Vector *SL_v_diffDouble(SL_v_Vector *lhs, SL_v_Vector *rhs);

double SL_v_dotDouble(SL_v_Vector *lhs, SL_v_Vector *rhs);

SL_m_Matrix *SL_v_toMatrix(SL_v_Vector *vector);
