/*!
 * @author fexolm 
 * @date 05.04.18.
 *
 * @brief Matrix data structure implementation
 */
#pragma once

#include <stdbool.h>
#include "block.h"

/*!
 * @brief matrix representation
 */
typedef struct {
  __SL_b_Block *block;
  size_t block_width;
  size_t block_height;
  size_t height;
  size_t width;
  size_t offsetX;
  size_t offsetY;
  bool transpose;
} __SL_m_Matrix;

/*!
 * @brief allocate matrix of type double
 * @return matrix with {width} cols and {height} rows
 */
__SL_m_Matrix *__SL_m_allocDouble(size_t width, size_t height);

/*!
 * @brief free memory from matrix
 */
void __SL_m_destroy(__SL_m_Matrix *matrix);

/*!
 * @brief create new matrix with same block with {matrix}
 * @return new matrix with same block with {matrix}
 */
__SL_m_Matrix *__SL_m_share(__SL_m_Matrix *matrix);

/*!
 * @brief create full copy of matrix (it means that all fields
 * in new matrix structure, except block pointer would be same as in {matrix}
 * @return full copy of matrix
 */
__SL_m_Matrix *__SL_m_fullCopy(__SL_m_Matrix *matrix);

/*!
 * @brief transpose matrix
 * @param matrix
 */
void __SL_m_transpose(__SL_m_Matrix *matrix);

/*!
 * @brief return matrix element on index x, y
 */
double __SL_m_getElementDouble_(__SL_m_Matrix *matrix, int x, int y);

/*!
 * @brief set matrix element on index x, y
 */
void __SL_m_setElementDouble(__SL_m_Matrix *matrix, int x, int y, double value);

/*!
 * @brief create copy of matrix with block_{height,width} = matrix.{height,width},
 * zero offsets and not transposed
 *
  * @note new matrix size would be less or equal {matrix} size
 *
 * @todo optimize get/set elements (does't need to use {get,set}element every time)
 */
__SL_m_Matrix *__SL_m_copyDouble(__SL_m_Matrix *matrix);

/*!
 * @brief return submatrix with row starting at xbegin on original matrix
 */
__SL_m_Matrix *__SL_m_getSlice(__SL_m_Matrix *matrix, int xbegin, int ybegin, size_t width, size_t height);





