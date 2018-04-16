/*!
 * @author fexolm 
 * @date 16.04.18.
 */
#pragma once

#include "block.h"
typedef struct {
  SL_b_Block *block;
  size_t offset;
  size_t size;
} SL_v_Vector;

SL_v_Vector *SL_v_allocDouble(size_t size);

void SL_v_destroy(SL_v_Vector *vector);

SL_v_Vector *SL_v_share(SL_v_Vector *vector);

SL_v_Vector *SL_v_fullCopy(SL_v_Vector *vector);

double SL_v_getElementDouble(SL_v_Vector *vector, size_t ind);

void SL_v_setElementDouble(SL_v_Vector *vector, size_t ind, double value);

SL_v_Vector *SL_v_slice(SL_v_Vector *vector, int begin, size_t width);

SL_v_Vector *SL_v_copyDouble(SL_v_Vector *vector);


