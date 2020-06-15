#pragma once

/// \file solve.h
///
/// Solving linear systems of equations.
///
/// A linear equation is presented as follows:
/// \code
/// Ax = b
/// \endcode
/// ... where the goal is to solve for solution \p x, given matrix \p A and product \p b.

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

/// Solve a linear system of equations in two steps:
/// 1) Gauss elimination A -> U
/// 2) Back substitution to solve <p>Ux = c</p> for \p x.
///
/// \pre The row count of \p i_matrix and \em must equal the row count of \p i_product.
///
/// \tparam MatrixT the left-hand side matrix type.
/// \tparam ProductT the matrix product type.
/// \tparam SolutionT the matrix solution type, which will
///
/// \param i_matrix the lhs matrix.
/// \param i_product the matrix product.
///
/// \return the solution matrix.
template < typename MatrixT,
           typename ProductT,
           typename SolutionT = Matrix< MatrixT::RowCount(), ProductT::ColumnCount(), typename MatrixT::ValueType > >
inline SolutionT Solve( const MatrixT& i_matrix, const ProductT& i_product )
{
    static_assert( MatrixT::RowCount() == ProductT::RowCount() );
    // TODO.
}

LINEAR_ALGEBRA_NS_CLOSE
