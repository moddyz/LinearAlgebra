#pragma once

/// \file setIdentity.h
///
/// Operation which sets an matrix to the identity element (I).
///
/// The identity matrix has 1's down its main diagonal, and 0 for all other entries.
/// This operation can only be applied to square matrices (M X M matrices).

#include <type_traits>

LINEAR_ALGEBRA_NS_OPEN

// Implementation detail:
// To un-roll the set identity operation at compile-time, we use compile-time recursion via enable_if with
// a two overload(s).

// This is the terminating overload chosen when RowIndex and ColumnIndex is equal to the row and column sizes of
// MatrixT, respectively.
template < typename MatrixT, int RowIndex, int ColumnIndex >
typename std::enable_if< RowIndex == MatrixT::GetRowSize() && ColumnIndex == MatrixT::GetColumnSize() >::type
_SetIdentity( MatrixT& o_matrix )
{
    // Nothing to do in this terminating overload.
}

// This is the operation step overload is chosen when RowIndex and ColumnIndex is not equal to the row and column sizes
// of MatrixT, respectively. The matrix entry (RowIndex, ColumnIndex) is set here.
template < typename MatrixT, int RowIndex = 0, int ColumnIndex = 0 >
typename std::enable_if< RowIndex != MatrixT::GetRowSize() && ColumnIndex != MatrixT::GetColumnSize() >::type
_SetIdentity( MatrixT& o_matrix )
{
    // Only square matrices have an identity element.
    static_assert( MatrixT::GetRowSize() == MatrixT::GetColumnSize() );

    // This is the operation, which is applied to all matrix entries when the row index == column index.
    o_matrix( RowIndex, ColumnIndex ) = 1;

    // Recurse into the next RowIndex == ColumnIndex entry.
    _SetIdentity< MatrixT, RowIndex + 1, ColumnIndex + 1 >( o_matrix );
}

/// Set the matrix \p o_matrix to the identity matrix.
///
/// \tparam MatrixT the matrix type.
template < typename MatrixT >
void SetIdentity( MatrixT& o_matrix )
{
    static_assert( MatrixT::GetRowSize() == MatrixT::GetColumnSize() );
    _SetIdentity< MatrixT, 0, 0 >( o_matrix );
}

LINEAR_ALGEBRA_NS_CLOSE
