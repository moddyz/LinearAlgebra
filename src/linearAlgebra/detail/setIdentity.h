#pragma once

/// \file detail/setIdentity.h
///
/// Implementation detail for compile-time identity matrix production.
///
/// The SetIdentity operation is unrolled at compile-time, using template recursion with a two overload(s).

#include <type_traits>

LINEAR_ALGEBRA_NS_OPEN

/// Overload code path taken to \em terminate the recursion.
///
/// The template recursion terminates When \p RowIndex and \p ColumnIndex is equal to the row and column sizes of
/// \p MatrixT, respectively.
template < typename MatrixT, int RowIndex, int ColumnIndex >
typename std::enable_if< RowIndex == MatrixT::RowCount() && ColumnIndex == MatrixT::ColumnCount() >::type
_SetIdentity( MatrixT& o_matrix )
{
    // Nothing to do in this terminating overload.
}

/// Overload code path taken to set \p 1 on one of the main diagonal entries of the matrix \p o_matrix,
///
/// This overload code path is taken when \p RowIndex and \p ColumnIndex is not yet equal to the row and column sizes.
template < typename MatrixT, int RowIndex = 0, int ColumnIndex = 0 >
typename std::enable_if< RowIndex != MatrixT::RowCount() && ColumnIndex != MatrixT::ColumnCount() >::type
_SetIdentity( MatrixT& o_matrix )
{
    // Only square matrices have an identity element.
    static_assert( MatrixT::RowCount() == MatrixT::ColumnCount() );

    // This is the operation, which is applied to all matrix entries when the row index == column index.
    o_matrix( RowIndex, ColumnIndex ) = 1;

    // Recurse into the next RowIndex == ColumnIndex entry.
    _SetIdentity< MatrixT, RowIndex + 1, ColumnIndex + 1 >( o_matrix );
}

LINEAR_ALGEBRA_NS_CLOSE
