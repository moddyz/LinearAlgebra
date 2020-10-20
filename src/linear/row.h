#pragma once

/// \file row.h
/// \ingroup LinearAlgebra_Operations
///
/// Row operations to perform on a Matrix.

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

    constexpr size_t         columnCount = MatrixT::ColumnCount();
    Matrix< 1, columnCount > rowA        = o_matrix.GetRow( i_rowIndexA );

    o_matrix.SetRow( i_rowIndexA, o_matrix.GetRow( i_rowIndexB ) );
    o_matrix.SetRow( i_rowIndexB, rowA );
}

LINEAR_NS_CLOSE
