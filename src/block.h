/*!
 * @author fexolm 
 * @date 08.04.18.
 */
#pragma once

#include <stddef.h>
/*!
 * @brief memory block with links counter
 */
typedef struct {
  size_t len;
  void *mem;
  int links;
} SL_b_Block;

/*!
 * @brief alloc block with len bytes
 * @param len - size of memory to alloc
 * @return __SL_m_block with len bytes
 */
SL_b_Block *SL_b_alloc(size_t len);

/*!
 * @brief decrement links counter and destroy block if counter = 0
 * @param block - block to destroy
 */
void SL_b_destroy(SL_b_Block *block);

/*!
 * @brief add link to block link counter and return that block
 * @param block - block n links
 * @return block with n+1 links
 */
SL_b_Block *SL_b_share(SL_b_Block *block);

/*!
 * @brief make a copy of block
 * @param block with n links
 * @return new block with 1 link
 */
SL_b_Block *SL_b_copy(const SL_b_Block *const block);

/*!
 * @brief swap memory in 2 blocks
 * @note blocks should have same sizek
 */
void SL_b_swap(SL_b_Block *lhs, SL_b_Block *rhs);