#pragma once

/// \file setIdentity.h
///
/// Operation which sets an matrix to the identity element (I).
///
/// The identity matrix has 1's down its main diagonal, and 0 for all other entries.
/// This operation can only be applied to square matrices (M X M matrices).

#include <linear/detail/diagonalOperations.h>
#include <linear/detail/matrixEntryOperators.h>

LINEAR_ALGEBRA_NS_OPEN

/// Set the matrix \p o_matrix to the identity matrix.
///
/// \pre \p o_matrix must be a square matrix.
///
/// \tparam MatrixT the matrix type.
template < typename MatrixT >
void SetIdentity( MatrixT& o_matrix )
{
    DiagonalUnaryOperation( MatrixEntrySet< MatrixT >( 1 ), o_matrix );
}

LINEAR_ALGEBRA_NS_CLOSE
