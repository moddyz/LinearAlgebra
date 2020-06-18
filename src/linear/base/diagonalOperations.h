#pragma once

/// \file diagonalOperations.h
///
/// Compile-time recursion for performing an operation across the diagonal of set of matrices, which allow for
/// row-column indexing.
///
/// For example, to set the corresponding entries of matrices \p A and \p B, and store into matrix \p C:
/// \code{.cpp}
/// linear::Matrix< 5, 5 > A;
/// linear::DiagonalMatrixOperation( ArrayEntryAddition< A::MatrixType >, A, B, C );
/// \endcode

#include <type_traits>

LINEAR_ALGEBRA_NS_OPEN

/// The \em terminating code path taken when performing a unary operation each diagonal entry of matrix \p o_matrix.
///
/// \pre \p o_matrix must be a square matrix (number of rows == number of rows).
///
/// \tparam MatrixEntryOperatorT the function prototype of the operation to perform.
/// \tparam MatrixT the array type.
/// \tparam RowIndex the row index of the matrix entry to operate on.
/// \tparam ColumnIndex the column index of the matrix entry to operate on.
///
/// \param i_operator the unary operator used.
/// \param o_matrix the modified matrix.
///
/// The template recursion terminates When \p RowIndex and \p ColumnIndex is equal to the row and column sizes of
/// \p MatrixT, respectively.
template < typename MatrixEntryOperatorT,
           typename MatrixT,
           int RowIndex    = 0,
           int ColumnIndex = 0,
           typename std::enable_if< RowIndex == MatrixT::RowCount() && ColumnIndex == MatrixT::ColumnCount() >::type* =
               nullptr >
void DiagonalUnaryOperation( MatrixEntryOperatorT i_operator, MatrixT& o_matrix )
{
    // Nothing to do in this terminating overload.
}

/// The \em operational code path taken to perform a unary operation each diagonal entry of matrix \p o_matrix.
///
/// \pre \p o_matrix must be a square matrix (number of rows == number of rows).
///
/// \tparam MatrixEntryOperatorT the function prototype of the binary operation to perform.
/// \tparam MatrixT the array type.
/// \tparam RowIndex the row index of the matrix entry to operate on.
/// \tparam ColumnIndex the column index of the matrix entry to operate on.
///
/// \param i_operator the unary operator used.
/// \param o_matrix the modified matrix.
///
/// This overload code path is taken when \p RowIndex and \p ColumnIndex is not yet equal to the row and column sizes.
template < typename MatrixEntryOperatorT,
           typename MatrixT,
           int RowIndex    = 0,
           int ColumnIndex = 0,
           typename std::enable_if< RowIndex != MatrixT::RowCount() && ColumnIndex != MatrixT::ColumnCount() >::type* =
               nullptr >
void DiagonalUnaryOperation( MatrixEntryOperatorT i_operator, MatrixT& o_matrix )
{
    // Only square matrices permit a diagonal operation.
    static_assert( MatrixT::RowCount() == MatrixT::ColumnCount() );

    // Call the operator.
    i_operator( RowIndex, ColumnIndex, o_matrix );

    // Recurse into the next RowIndex == ColumnIndex entry.
    DiagonalUnaryOperation< MatrixEntryOperatorT, MatrixT, RowIndex + 1, ColumnIndex + 1 >( i_operator, o_matrix );
}

LINEAR_ALGEBRA_NS_CLOSE
