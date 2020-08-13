#pragma once

/// \file row.h
/// \ingroup LinearAlgebra_Operations
///
/// Query or manipulate the rows of a Matrix.

#include <linear/matrix.h>

LINEAR_NS_OPEN

/// Exchange rows of of a matrix, in-place.
/// \ingroup LinearAlgebra_Operations
///
/// \tparam MatrixT the type of matrix.
///
/// \param i_rowIndexA the index of one row.
/// \param i_rowIndexB the index of the other row.
/// \param o_matrix the matrix to perform the row exchange on.
template < typename MatrixT >
void RowExchange( size_t i_rowIndexA, size_t i_rowIndexB, MatrixT& o_matrix )
{
    LINEAR_ASSERT( i_rowIndexA < MatrixT::RowCount() );
    LINEAR_ASSERT( i_rowIndexB < MatrixT::RowCount() );
    LINEAR_ASSERT( i_rowIndexA != i_rowIndexB );

    constexpr size_t columnCount = MatrixT::ColumnCount();

    // Temporarily take out copy of row A.
    Matrix< 1, columnCount > rowA = o_matrix.GetRow( i_rowIndexA );

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

LINEAR_NS_CLOSE
