/*!
 * @author fexolm 
 * @date 05.04.18.
 *
 * @brief Matrix data structure implementation
 *
 * @todo
 *  - add implement const matrix share
 *  - implement reshape
 */
#pragma once

#include <stdbool.h>
#include "block.h"

/*!
 * @brief matrix representation
 */

typedef struct __Vector SL_v_Vector;

typedef struct __Matrix {
  SL_b_Block *block;
  size_t block_width;
  size_t height;
  size_t width;
  size_t offsetX;
  size_t offsetY;
  bool transpose;
} SL_m_Matrix;

/*!
 * @brief allocate matrix of type double
 * @return matrix with {width} cols and {height} rows
 */
SL_m_Matrix *SL_m_allocDouble(size_t width, size_t height);

/*!
 * @brief free memory from matrix
 */
void SL_m_destroy(SL_m_Matrix *matrix);

/*!
 * @brief create new matrix with same block with {matrix}
 * @return new matrix with same block with {matrix}
 */
SL_m_Matrix *SL_m_share(SL_m_Matrix *matrix);

/*!
 * @brief create full copy of matrix (it means that all fields
 * in new matrix structure, except block pointer would be same as in {matrix}
 * @return full copy of matrix
 */
SL_m_Matrix *SL_m_fullCopy(SL_m_Matrix *matrix);

/*!
 * @brief transpose matrix
 * @param matrix
 */
void SL_m_transpose(SL_m_Matrix *matrix);

/*!
 * @brief return matrix element on index x, y
 */
double SL_m_getElementDouble(SL_m_Matrix *matrix, int x, int y);

/*!
 * @brief set matrix element on index x, y
 */
void SL_m_setElementDouble(SL_m_Matrix *matrix, int x, int y, double value);

/*!
 * @brief create copy of matrix with block_{height,width} = matrix.{height,width},
 * zero offsets and not transposed
 *
  * @note new matrix size would be less or equal {matrix} size
 *
 * @todo optimize get/set elements (does't need to use {get,set}element every time)
 */
SL_m_Matrix *SL_m_copyDouble(SL_m_Matrix *matrix);

/*!
 * @brief return submatrix with row starting at xbegin on original matrix
 */
SL_m_Matrix *SL_m_slice(SL_m_Matrix *matrix, int xbegin, int ybegin, size_t width, size_t height);

SL_v_Vector *SL_m_toVector(SL_m_Matrix *matrix);





