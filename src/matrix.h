/*!
 * @author fexolm 
 * @date 05.04.18.
 *
 * @brief Matrix data structure implementation
 */
#pragma once

/*!
 * @brief memory block with links counter
 */
typedef struct {
  size_t len;
  void *mem;
  int links;
} __SL_m_block;

/*!
 * @brief alloc block with len bytes
 *
 * @param len - size of memory to alloc
 * @return __SL_m_block with len bytes
 */
__SL_m_block *__SL_m_allocBlock(size_t len);

/*!
 * @brief decrement links counter and destroy block if counter = 0
 * @param block - block to destroy
 */
void __SL_m_destroyBlock(__SL_m_block *block);

/*!
 * @brief add link to block link counter and return that block
 * @param block - block n links
 * @return block with n+1 links
 */
__SL_m_block *__SL_m_addLink(__SL_m_block *block);

/*!
 * @brief make a copy of block
 * @param block with n links
 * @return new block with 1 link
 */
__SL_m_block *__SL_m_copyBlock(const __SL_m_block *const block);

/*!
 * @brief swap memory in 2 blocks
 * @param lhs - left block
 * @param rhs - right block
 *
 * @note blocks should have same sizek
 *
 */
void __SL_m_swapBlocks(__SL_m_block *lhs, __SL_m_block *rhs);