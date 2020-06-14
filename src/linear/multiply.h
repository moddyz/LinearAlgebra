#pragma once

/// \file multiply.h
///
/// Matrix mutiplication (A * B = AB).
///
/// Mathematically described as the composition of two linear maps.
///
/// Each entry (i, j) in the matrix product AB can be computed as the inner product of the \em i'th
/// row of A and the \em j'th column of B.

#include <linear/linear.h>
#include <linear/matrix.h>

#include <linear/base/multiplyImpl.h>

LINEAR_ALGEBRA_NS_OPEN

/// Multiply matrices \p i_lhs and \p i_rhs, and return the matrix product.
///
/// \pre the \ref Matrix::ColumnCount of \p i_lhs must equal the \ref Matrix::RowCount of \p i_rhs.
///
/// The matrix product will assume the shape (\ref RowCount() of \p i_lhs, \ref ColumnCount() of \p i_rhs).
///
/// \tparam LeftMatrixT the type of the left-hand side matrix.
/// \tparam RightMatrixT the type of the right-hand side matrix.
/// \tparam MatrixProductT the type of the matrix product.
///
/// \param i_lhs left-hand side matrix.
/// \param i_rhs right-hand side matrix.
///
/// \return the matrix product.
template < typename LeftMatrixT,
           typename RightMatrixT,
           typename MatrixProductT =
               Matrix< LeftMatrixT::RowCount(), RightMatrixT::ColumnCount(), typename LeftMatrixT::ValueType > >
constexpr inline MatrixProductT MatrixMultiplication( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs )
{
    static_assert( LeftMatrixT::ColumnCount() == RightMatrixT::RowCount() );
    return _MatrixMult< LeftMatrixT, RightMatrixT, MatrixProductT >( i_lhs, i_rhs );
}

LINEAR_ALGEBRA_NS_CLOSE
