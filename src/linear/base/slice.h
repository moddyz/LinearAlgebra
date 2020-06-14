#pragma once

/// \file slice.h
///
/// Tools for extracting a slice from an Matrix.

template < typename MatrixT,
           typename SliceT,
           size_t RowBegin,
           size_t ColumnBegin,
           typename RowIndices = std::make_index_sequence< SliceT::RowCount() >,
           typename ColumnIndices = std::make_index_sequence< SliceT::ColumnCount() > >
constexpr inline MatrixProductT MatrixSlice( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs )
{
    static_assert( LeftMatrixT::ColumnCount() == RightMatrixT::RowCount() );
    return _MatrixMultIndexExpansion< LeftMatrixT, RightMatrixT, MatrixProductT >( i_lhs, i_rhs, EntryIndices{} );
}
