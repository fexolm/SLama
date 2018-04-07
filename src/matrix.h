/*!
 * @author fexolm 
 * @date 05.04.18.
 *
 * @brief Matrix data structure implementation
 */
#pragma once

#include <stdbool.h>
/*!
 * @brief memory block with links counter
 */
typedef struct {
  size_t len;
  void *mem;
  int links;
} __SL_m_Block;

/*!
 * @brief alloc block with len bytes
 *
 * @param len - size of memory to alloc
 * @return __SL_m_block with len bytes
 */
__SL_m_Block *__SL_m_allocBlock(size_t len);

/*!
 * @brief decrement links counter and destroy block if counter = 0
 * @param block - block to destroy
 */
void __SL_m_destroyBlock(__SL_m_Block *block);

/*!
 * @brief add link to block link counter and return that block
 * @param block - block n links
 * @return block with n+1 links
 */
__SL_m_Block *__SL_m_addLink(__SL_m_Block *block);

/*!
 * @brief make a copy of block
 * @param block with n links
 * @return new block with 1 link
 */
__SL_m_Block *__SL_m_copyBlock(const __SL_m_Block *const block);

/*!
 * @brief swap memory in 2 blocks
 * @param lhs - left block
 * @param rhs - right block
 *
 * @note blocks should have same sizek
 *
 */
void __SL_m_swapBlocks(__SL_m_Block *lhs, __SL_m_Block *rhs);

/*!
 * @brief matrix representation
 */
typedef struct {
  __SL_m_Block *block;
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
 *
 * @param width - matrix width
 * @param height - matrix height
 * @return matrix with {width} cols and {height} rows
 */
__SL_m_Matrix *__SL_m_allocMatrix_double(size_t width, size_t height);

/*!
 * @brief free memory from matrix
 *
 * @param matrix
 */
void __SL_m_destroyMatrix(__SL_m_Matrix *matrix);

/*!
 * @brief create new matrix with same block with {matrix}
 * @param matrix
 * @return new matrix with same block with {matrix}
 */
__SL_m_Matrix *__SL_m_shareMatrix(__SL_m_Matrix *matrix);

/*!
 * @brief create full copy of matrix
 * @param matrix
 * @return full copy of matrix
 */
__SL_m_Matrix *__SL_m_copyMatrix(__SL_m_Matrix *matrix);

/*!
 * @brief transpose matrix
 * @param matrix
 */
void __SL_m_transposeMatrix(__SL_m_Matrix *matrix);

/*!
 * @brief return matrix element on index x, y
 * @param matrix
 * @param x - col
 * @param y - row
 * @return element on index x, y
 */
double __SL_m_getMatrixElement_double(__SL_m_Matrix *matrix, int x, int y);

/*!
 * @brief set matrix element on index x, y
 * @param matrix
 * @param x - col
 * @param y - row
 */
void __SL_m_setMatrixElement_double(__SL_m_Matrix *matrix, int x, int y, double value);





