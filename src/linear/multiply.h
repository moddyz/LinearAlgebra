#pragma once

/// \file multiply.h
///
/// Matrix multiplication API.

#include <linear/base/matrixMultiplication.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Multiply matrices \p i_lhs and \p i_rhs, and return the matrix product.
///
/// \pre the \ref Matrix::ColumnCount of \p i_lhs must equal the \ref Matrix::RowCount of \p i_rhs.
///
/// The matrix product will assume the shape (\ref RowCount() of \p i_lhs, \ref ColumnCount() of \p i_rhs).
///
/// \tparam LHSMatrixT the type of the left-hand side matrix.
/// \tparam RHSMatrixT the type of the right-hand side matrix.
/// \tparam MatrixProductT the type of the matrix product.
///
/// \param i_lhs left-hand side matrix.
/// \param i_rhs right-hand side matrix.
///
/// \return the matrix product.
template < typename LHSMatrixT,
           typename RHSMatrixT,
           typename MatrixProductT =
               Matrix< LHSMatrixT::RowCount(), RHSMatrixT::ColumnCount(), typename LHSMatrixT::ValueType > >
constexpr inline MatrixProductT Multiply( const LHSMatrixT& i_lhs, const RHSMatrixT& i_rhs )
{
    static_assert( LHSMatrixT::ColumnCount() == RHSMatrixT::RowCount() );
    return _MatrixMult< LHSMatrixT, RHSMatrixT, MatrixProductT >( i_lhs, i_rhs );
}

LINEAR_ALGEBRA_NS_CLOSE
