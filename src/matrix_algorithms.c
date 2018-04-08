/*!
 * @author fexolm 
 * @date 08.04.18.
 */
#include <assert.h>
#include "matrix_algorithms.h"

static inline void __sumInto(SL_m_Matrix *result, SL_m_Matrix *lhs, SL_m_Matrix *rhs) {
  assert(lhs->height==rhs->height && lhs->width==rhs->width && "Matrix should be same length");
  for (int x = 0; x < lhs->width; x++) {
    for (int y = 0; y < lhs->height; y++) {
      SL_m_setElementDouble(result, x, y, SL_m_getElementDouble(lhs, x, y) + SL_m_getElementDouble(rhs, x, y));
    }
  }
}

static inline void __diffInto(SL_m_Matrix *result, SL_m_Matrix *lhs, SL_m_Matrix *rhs) {
  assert(lhs->height==rhs->height && lhs->width==rhs->width && "Matrix should be same length");
  for (int x = 0; x < lhs->width; x++) {
    for (int y = 0; y < lhs->height; y++) {
      SL_m_setElementDouble(result, x, y, SL_m_getElementDouble(lhs, x, y) - SL_m_getElementDouble(rhs, x, y));
    }
  }
}

void SL_m_addDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs) {
  __sumInto(lhs, lhs, rhs);
}
SL_m_Matrix *SL_m_sumDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs) {
  SL_m_Matrix *result = SL_m_allocDouble(lhs->width, lhs->height);
  __sumInto(result, lhs, rhs);
  return result;
}
void SL_m_substractDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs) {
  __diffInto(lhs, lhs, rhs);
}
SL_m_Matrix *SL_m_diffDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs) {
  SL_m_Matrix *result = SL_m_allocDouble(lhs->width, lhs->height);
  __diffInto(result, lhs, rhs);
  return result;
}
void SL_m_multByDouble(SL_m_Matrix *matrix, double scalar) {
  for (int x = 0; x < matrix->width; x++) {
    for (int y = 0; y < matrix->height; y++) {
      SL_m_setElementDouble(matrix, x, y, SL_m_getElementDouble(matrix, x, y)*scalar);
    }
  }
}
SL_m_Matrix *SL_m_matmulDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs) {
  assert(lhs->width==rhs->height && "Can not multiply matrices (invalid shapes)");
  SL_m_Matrix *result = SL_m_allocDouble(rhs->width, lhs->height);

  for (int y = 0; y < lhs->height; y++) {
    for (int x = 0; x < rhs->width; x++) {
      double val = 0;
      for (int r = 0; r < lhs->width; r++) {
        val += SL_m_getElementDouble(lhs, r, y)*SL_m_getElementDouble(rhs, x, r);
      }
      SL_m_setElementDouble(result, x, y, val);
    }
  }
  return result;
}
