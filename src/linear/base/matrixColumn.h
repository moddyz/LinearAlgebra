#pragma once

/// \file matrixColumn.h
///
/// Implementation details for extracting a column of a Matrix (compile-time supported).

#include <linear/linear.h>

LINEAR_NS_OPEN

/// Index sequence expansion into packed parameters, to initialize the column matrix.
template < typename MatrixT, typename ColumnT, std::size_t... RowIndex >
constexpr inline ColumnT
_MatrixColumnIndexExpansion( const MatrixT& i_matrix, size_t i_colIndex, std::index_sequence< RowIndex... > )
{
    return ColumnT( ( i_matrix( RowIndex, i_colIndex ) )... );
}

/// Generates a index sequence of the same length as the number of entries in a single column of \p i_matrix.
template < typename MatrixT,
           typename ColumnT,
           typename RowIndices = std::make_index_sequence< MatrixT::RowCount() > >
constexpr inline ColumnT _MatrixColumn( const MatrixT& i_matrix, size_t i_colIndex )
{
    return _MatrixColumnIndexExpansion< MatrixT, ColumnT >( i_matrix, i_colIndex, RowIndices{} );
}

LINEAR_NS_CLOSE
