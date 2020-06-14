#pragma once

/// \file identityImpl.h
///
/// Implementation details to produce a compile-time generated matrix product.

LINEAR_ALGEBRA_NS_OPEN

template < typename LeftMatrixT,
           typename RightMatrixT,
           typename MatrixProductT,
           std::size_t RowIndex,
           std::size_t ColIndex,
           std::size_t... InnerProductIndex >
constexpr inline typename MatrixProductT::ValueType
_InnerProductIndexExpansion( const LeftMatrixT&  i_lhs,
                             const RightMatrixT& i_rhs,
                             std::index_sequence< InnerProductIndex... > )
{
    return ( ( i_lhs( RowIndex, InnerProductIndex ) * i_rhs( InnerProductIndex, ColIndex ) ) + ... );
}

template < typename LeftMatrixT,
           typename RightMatrixT,
           typename MatrixProductT,
           std::size_t EntryIndex,
           typename InnerProductIndices = std::make_index_sequence< LeftMatrixT::ColumnCount() > >
constexpr inline typename MatrixProductT::ValueType _InnerProduct( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs )
{
    const std::size_t rowIndex    = EntryIndex / MatrixProductT::ColumnCount();
    const std::size_t columnIndex = EntryIndex % MatrixProductT::ColumnCount();
    return _InnerProductIndexExpansion< LeftMatrixT, RightMatrixT, MatrixProductT, rowIndex, columnIndex >( i_lhs, i_rhs, InnerProductIndices{} );
}

template < typename LeftMatrixT, typename RightMatrixT, typename MatrixProductT, std::size_t... EntryIndex >
constexpr inline MatrixProductT
_MatrixMultIndexExpansion( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs, std::index_sequence< EntryIndex... > )
{
    return MatrixProductT( _InnerProduct< LeftMatrixT, RightMatrixT, MatrixProductT, EntryIndex >( i_lhs, i_rhs )... );
}

template < typename LeftMatrixT,
           typename RightMatrixT,
           typename MatrixProductT,
           typename EntryIndices = std::make_index_sequence< MatrixProductT::EntryCount() > >
constexpr inline MatrixProductT _MatrixMult( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs )
{
    static_assert( LeftMatrixT::ColumnCount() == RightMatrixT::RowCount() );
    return _MatrixMultIndexExpansion< LeftMatrixT, RightMatrixT, MatrixProductT >( i_lhs, i_rhs, EntryIndices{} );
}

LINEAR_ALGEBRA_NS_CLOSE
