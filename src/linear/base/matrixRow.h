#pragma once

/// \file matrixRow.h
///
/// Implementation details for extracting a row of a Matrix (compile-time supported).

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

/// Index sequence expansion into packed parameters, to initialize the row matrix.
template < typename MatrixT, typename RowT, std::size_t... ColumnIndex >
constexpr inline RowT
_MatrixRowIndexExpansion( const MatrixT& i_matrix, size_t i_rowIndex, std::index_sequence< ColumnIndex... > )
{
    return RowT( ( i_matrix( i_rowIndex, ColumnIndex ) )... );
}

/// Generates a index sequence of the same length as the number of entries in the row matrix.
template < typename MatrixT, typename RowT, typename ColumnIndices = std::make_index_sequence< MatrixT::ColumnCount() > >
constexpr inline RowT _MatrixRow( const MatrixT& i_matrix, size_t i_rowIndex )
{
    return _MatrixRowIndexExpansion< MatrixT, RowT >( i_matrix, i_rowIndex, ColumnIndices{} );
}

LINEAR_ALGEBRA_NS_CLOSE
