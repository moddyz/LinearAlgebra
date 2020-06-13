#pragma once

/// \file entryWise.h
///
/// Compile-time recursion for performing an unary operation on <em> each entry </em> of a Matrix, or a
/// binary operation on <em> corresponding entries</em> of two matrices.
///
/// For example, to add the corresponding entries of matrices A and B, and store into C:
///
/// \code{.cpp}
/// linear::Matrix< 5, 5 > A, B, C;
/// linear::EntryWiseBinaryOperation< decltype(A), linear::
/// \endcode

#include <type_traits>

LINEAR_ALGEBRA_NS_OPEN

/// Overload code path taken to \em terminate the recursion.
///
/// The template recursion terminates \p Index equals \ref Matrix::EntryCount().
template < typename BinaryOperatorT, typename MatrixT, int Index = 0 >
typename std::enable_if< Index == MatrixT::EntryCount() >::type
EntryWiseBinaryOperation( BinaryOperatorT i_operator, const MatrixT& i_lhs, const MatrixT& i_rhs, MatrixT& o_output )
{
    // Nothing to do in this terminating overload.
}

/// Overload code path taken to perform an entry-wise binary operation the matrices \p i_lhs and \p i_rhs, storing
/// the result in \p o_output.
///
/// \pre The \em shape of \p i_lhs, \p i_rhs, and \p o_output \em must be the same!
///
/// This overload code path is taken when \p Index is not equal the \ref Matrix::EntryCount().
template < typename BinaryOperatorT, typename MatrixT, int Index = 0 >
typename std::enable_if< Index != MatrixT::EntryCount() >::type
EntryWiseBinaryOperation( BinaryOperatorT i_operator, const MatrixT& i_lhs, const MatrixT& i_rhs, MatrixT& o_output )
{
    i_operator( Index, i_lhs, i_rhs, o_output );

    // Recurse into the next RowIndex == ColumnIndex entry.
    EntryWiseBinaryOperation< BinaryOperatorT, MatrixT, Index + 1 >( i_operator, i_lhs, i_rhs, o_output );
}

/// Entry-wise addition operator.
///
/// \param i_index the index of the matrix entry to add.
/// \param i_lhs the left-hand-side matrix.
/// \param i_rhs the right-hand-side matrix.
/// \param o_output the matrix to store the sum of the corresponding entries.
///
/// \tparam MatrixT the type of matrix.
template < typename MatrixT >
void EntryWiseAdditionOperator( size_t i_index, const MatrixT& i_lhs, const MatrixT& i_rhs, MatrixT& o_output )
{
    o_output[ i_index ] = i_lhs[ i_index ] + i_rhs[ i_index ] ;
}

LINEAR_ALGEBRA_NS_CLOSE
