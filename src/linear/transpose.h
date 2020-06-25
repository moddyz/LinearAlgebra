#pragma once

/// \file transpose.h
///
/// Matrix transpose.
///
/// Roughly speaking, transposing a matrix flips it across its main diagonal.
///
/// Or, more precisely:
/// - the rows of the original matrix become the columns of the transposed matrix.
/// - for each entry (i, j) in the original matrix, the corresponding transposed entry is (j, i)./

#include <linear/base/matrixTranspose.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_NS_OPEN

/// Find transpose of \p i_matrix.
///
/// \tparam MatrixT The input matrix type.
///
/// \param i_matrix The input matrix.
///
/// \return The transposed matrix.
template < typename MatrixT >
constexpr inline Matrix< MatrixT::ColumnCount(), MatrixT::RowCount(), typename MatrixT::ValueType >
Transpose( const MatrixT& i_matrix )
{
    return _MatrixTranspose( i_matrix );
}

LINEAR_NS_CLOSE
