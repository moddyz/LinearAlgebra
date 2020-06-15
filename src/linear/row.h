#pragma once

/// \file row.h
///
/// Matrix Row API.

#include <linear/base/matrixSlice.h>

#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Extract a row of a matrix.
///
/// \tparam MatrixT the type of matrix.
///
/// \param o_matrix the source matrix.
/// \param i_rowIndeB the index of the row to extract.
///
/// \return the row of a matrix.
template < typename MatrixT, typename RowT = Matrix< 1, MatrixT::ColumnCount(), typename MatrixT::ValueType > >
constexpr inline RowT GetRow( const MatrixT& i_matrix, size_t i_rowIndex )
{
    LINEAR_ALGEBRA_ASSERT( i_rowIndex < MatrixT::RowCount() );
    return _MatrixRow< MatrixT, RowT >( i_matrix, i_rowIndex );
}

/// Exchange rows of of a matrix, in-place.
///
/// \tparam MatrixT the type of matrix.
///
/// \param i_rowIndexA the index of one row.
/// \param i_rowIndexB the index of the other row.
/// \param o_matrix the matrix to perform the row exchange on.
template < typename MatrixT >
void RowExchange( size_t i_rowIndexA, size_t i_rowIndexB, MatrixT& o_matrix )
{
    LINEAR_ALGEBRA_ASSERT( i_rowIndexA < MatrixT::RowCount() );
    LINEAR_ALGEBRA_ASSERT( i_rowIndexB < MatrixT::RowCount() );
    LINEAR_ALGEBRA_ASSERT( i_rowIndexA != i_rowIndexB );

    constexpr size_t columnCount = MatrixT::ColumnCount();

    // Temporarily take out copy of row A.
    Matrix< 1, columnCount > rowA = GetRow( o_matrix, i_rowIndexA );

    // Copy row B -> row A.
    for ( size_t columnIndex = 0; columnIndex < columnCount; ++columnIndex )
    {
        o_matrix[ i_rowIndexA * columnCount + columnIndex ] = o_matrix[ i_rowIndexB * columnCount + columnIndex ];
    }

    // Copy row A -> row B.
    for ( size_t columnIndex = 0; columnIndex < columnCount; ++columnIndex )
    {
        o_matrix[ i_rowIndexB * columnCount + columnIndex ] = rowA[ columnIndex ];
    }
}

LINEAR_ALGEBRA_NS_CLOSE
