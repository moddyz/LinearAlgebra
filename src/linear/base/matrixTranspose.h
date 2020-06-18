#pragma once

/// \file matrixRow.h
///
/// Implementation details for transposing a M x N matrix (compile-time supported).

#include <linear/linear.h>

#include <iostream>

LINEAR_ALGEBRA_NS_OPEN

/// Converts a sequence index into the respective identity matrix value.
template < typename MatrixT, std::size_t EntryIndex >
constexpr typename MatrixT::ValueType _MatrixTransposeEntry( const MatrixT& i_matrix )
{
    const std::size_t rowIndex    = EntryIndex / MatrixT::RowCount();
    const std::size_t columnIndex = EntryIndex % MatrixT::RowCount();
    return i_matrix( columnIndex, rowIndex );
}

/// Expand each index sequence element \p EntryIndex, to form packed parameters to construct \p MatrixT.
template < typename MatrixT, std::size_t... EntryIndex >
constexpr inline Matrix< MatrixT::ColumnCount(), MatrixT::RowCount(), typename MatrixT::ValueType >
_MatrixTransposeIndexExpansion( const MatrixT& i_matrix, std::index_sequence< EntryIndex... > )
{
    return Matrix< MatrixT::ColumnCount(), MatrixT::RowCount(), typename MatrixT::ValueType >(
        _MatrixTransposeEntry< MatrixT, EntryIndex >( i_matrix )... );
}

/// Generate an index_sequence of size \ref Matrix::EntryCount().
template < typename MatrixT, typename EntryIndices = std::make_index_sequence< MatrixT::EntryCount() > >
constexpr inline Matrix< MatrixT::ColumnCount(), MatrixT::RowCount(), typename MatrixT::ValueType >
_MatrixTranspose( const MatrixT& i_matrix )
{
    return _MatrixTransposeIndexExpansion( i_matrix, EntryIndices{} );
}

LINEAR_ALGEBRA_NS_CLOSE
