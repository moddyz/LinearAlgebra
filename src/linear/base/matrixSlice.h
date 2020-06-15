#pragma once

/// \file slice.h
///
/// Implementation details for extracting a slice of a Matrix (compile-time supported).

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

/// Each entry index needs to be decomposed into the slice's row and column index, to extract the region of interest
/// from \p i_matrix.
template < typename MatrixT, typename SliceT, size_t RowOffset, size_t ColumnOffset, std::size_t EntryIndex >
constexpr inline typename SliceT::ValueType _MatrixSliceIndexDecompose( const MatrixT& i_matrix )
{
    const std::size_t rowIndex    = EntryIndex / SliceT::ColumnCount();
    const std::size_t columnIndex = EntryIndex % SliceT::ColumnCount();
    return i_matrix( RowOffset + rowIndex, ColumnOffset + columnIndex );
}

/// Index sequence expansion into packed parameters, to initialize the Slice matrix.
template < typename MatrixT, typename SliceT, size_t RowOffset, size_t ColumnOffset, std::size_t... EntryIndex >
constexpr inline SliceT _MatrixSliceIndexExpansion( const MatrixT& i_matrix, std::index_sequence< EntryIndex... > )
{
    return SliceT(
        ( _MatrixSliceIndexDecompose< MatrixT, SliceT, RowOffset, ColumnOffset, EntryIndex >( i_matrix ) )... );
}

/// Generates a index sequence of the same length as the number of entries in the slice matrix.
template < typename MatrixT,
           typename SliceT,
           size_t RowOffset,
           size_t ColumnOffset,
           typename SliceIndices = std::make_index_sequence< SliceT::EntryCount() > >
constexpr inline SliceT _MatrixSlice( const MatrixT& i_matrix )
{
    return _MatrixSliceIndexExpansion< MatrixT, SliceT, RowOffset, ColumnOffset >( i_matrix, SliceIndices{} );
}

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
