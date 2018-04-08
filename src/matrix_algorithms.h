/*!
 * @author fexolm 
 * @date 08.04.18.
 */
#pragma once
#include "matrix_core.h"

/*!
 * @brief computes {lhs} + {rhs}
 * store result in {lhs}
 *
 * @todo get rid of getElementDouble and setElementDouble
 */
void SL_m_addDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs);

/*!
 * @brief computes {lhs} + {rhs}
 * @return new matrix
 */
SL_m_Matrix *SL_m_sumDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs);

/*!
 * @brief computes {lhs} - {rhs}
 * store result in {lhs}
 *
 * @todo get rid of getElementDouble and setElementDouble
 */
void SL_m_substractDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs);

/*!
 * @brief computes {lhs} - {rhs}
 * @return new matrix
 */
SL_m_Matrix *SL_m_diffDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs);

/*!
 * @brief multiply matrix on scalar inplace
 */
void SL_m_multByDouble(SL_m_Matrix *matrix, double scalar);

/*!
 * @brief matrix multiplication
 * @return matrices product
 *
 * @todo optimize
 * maybe use pthread to parallel multiplicaton
 */
SL_m_Matrix *SL_m_matmulDouble(SL_m_Matrix *lhs, SL_m_Matrix *rhs);
