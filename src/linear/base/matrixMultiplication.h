#pragma once

/// \file matrixMultiplication.h
///
/// Matrix mutiplication implementation details of compile-time supported matrix multiplication.
///
/// The entry point is \ref linear::_MatrixMult, so read from bottom up.

#include <linear/linear.h>

LINEAR_NS_OPEN

/// Inner product computation of the \p RowIndex'th row of \p i_lhs and the \p ColumnIndex'th column of \p i_rhs.
///
/// Expands the index sequence into packed parameters and perform a sum of the product(s), for \p N number of entries:
/// \code
/// lhs( Row, 0 ) * rhs( 0, Col ) + lhs( Row, 1 ) * rhs( 1, Col ) + ... + lhs( Row, N ) * rhs( N, Col )
/// \endcode
///
/// \return the inner product.
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

/// An index sequence is generated with the same length as the column count of \p i_lhs (or, row count of \p i_rhs).
/// Forwards this inner product index sequence to \ref _InnerProductIndexExpansion, for expansion.
///
/// The row and column indices are resolved, row-major-wise, into row and column indices.
///
/// \return the inner product.
template < typename LeftMatrixT,
           typename RightMatrixT,
           typename MatrixProductT,
           std::size_t EntryIndex,
           typename InnerProductIndices = std::make_index_sequence< LeftMatrixT::ColumnCount() > >
constexpr inline typename MatrixProductT::ValueType _InnerProduct( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs )
{
    // The Matrix class stores its entries row-major, thus we compute the row, column indices from the entry index
    // by from the column count.
    const std::size_t rowIndex    = EntryIndex / MatrixProductT::ColumnCount();
    const std::size_t columnIndex = EntryIndex % MatrixProductT::ColumnCount();
    return _InnerProductIndexExpansion< LeftMatrixT, RightMatrixT, MatrixProductT, rowIndex, columnIndex >(
        i_lhs,
        i_rhs,
        InnerProductIndices{} );
}

/// Expands the index sequence into a packed parameters to construct \p MatrixProductT, via a fold expression.
///
/// Each parameter is computed as the \ref _InnerProduct of a row of \p i_lhs and a column of \p i_rhs.
///
/// \return the matrix product.
template < typename LeftMatrixT, typename RightMatrixT, typename MatrixProductT, std::size_t... EntryIndex >
constexpr inline MatrixProductT
_MatrixMultIndexExpansion( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs, std::index_sequence< EntryIndex... > )
{
    return MatrixProductT( _InnerProduct< LeftMatrixT, RightMatrixT, MatrixProductT, EntryIndex >( i_lhs, i_rhs )... );
}

/// Generates an index sequence \p EntryIndices of the same length as the entry count of \p MatrixProductT.
///
/// Forwards the index sequence to \ref _MatrixMultIndexExpansion, for expansion.
///
/// \return the matrix product.
template < typename LeftMatrixT,
           typename RightMatrixT,
           typename MatrixProductT,
           typename EntryIndices = std::make_index_sequence< MatrixProductT::EntryCount() > >
constexpr inline MatrixProductT _MatrixMult( const LeftMatrixT& i_lhs, const RightMatrixT& i_rhs )
{
    static_assert( LeftMatrixT::ColumnCount() == RightMatrixT::RowCount() );
    return _MatrixMultIndexExpansion< LeftMatrixT, RightMatrixT, MatrixProductT >( i_lhs, i_rhs, EntryIndices{} );
}

LINEAR_NS_CLOSE
