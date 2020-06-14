#pragma once

/// \file slice.h
///
/// Tools for extracting a slice from an Matrix.

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

template < typename MatrixT, typename SliceT, size_t RowBegin, size_t ColumnBegin, std::size_t EntryIndex >
constexpr inline typename SliceT::ValueType _MatrixSliceIndexDecompose( const MatrixT& i_matrix )
{
    const std::size_t rowIndex    = EntryIndex / SliceT::ColumnCount();
    const std::size_t columnIndex = EntryIndex % SliceT::ColumnCount();
    return i_matrix( RowBegin + rowIndex, ColumnBegin + columnIndex );
}

template < typename MatrixT, typename SliceT, size_t RowBegin, size_t ColumnBegin, std::size_t... EntryIndex >
constexpr inline SliceT _MatrixSliceIndexExpansion( const MatrixT& i_matrix, std::index_sequence< EntryIndex... > )
{
    return SliceT(
        ( _MatrixSliceIndexDecompose< MatrixT, SliceT, RowBegin, ColumnBegin, EntryIndex >( i_matrix ) )... );
}

template < typename MatrixT,
           typename SliceT,
           size_t RowBegin,
           size_t ColumnBegin,
           typename SliceIndices = std::make_index_sequence< SliceT::EntryCount() > >
constexpr inline SliceT _MatrixSlice( const MatrixT& i_matrix )
{
    return _MatrixSliceIndexExpansion< MatrixT, SliceT, RowBegin, ColumnBegin >( i_matrix, SliceIndices{} );
}

LINEAR_ALGEBRA_NS_CLOSE
