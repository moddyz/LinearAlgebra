#pragma once

/// \file rank.h
/// \ingroup LinearAlgebra_Operations
///
/// Matrix rank.
///
/// The \em rank of a matrix is the number of pivot columns it possesses, or in other words,
/// the number of independent columns.

#include <linear/linear.h>
#include <linear/matrix.h>

#include <linear/base/matrixEntryArray.h>
#include <linear/base/matrixRowEchelon.h>

LINEAR_NS_OPEN

/// Compute the <em>maximum rank</em> a matrix of type \p MatrixT could potentially have.
/// \ingroup LinearAlgebra_Operations
///
/// \tparam MatrixT the matrix type.
///
/// \return the maximum rank of the matrix.
template < typename MatrixT >
constexpr inline size_t MaxRank()
{
    return std::min( MatrixT::RowCount(), MatrixT::ColumnCount() );
}

/// Compute the \em rank of matrix \p i_matrix.
/// \ingroup LinearAlgebra_Operations
///
/// The rank of a matrix is defined to be the number of its pivots, or independent columns.
///
/// \ingroup LinearAlgebra_Operations
///
/// \return the rank of the matrix.
template < typename MatrixT >
inline size_t Rank( const MatrixT& i_matrix )
{
    MatrixEntryArray< MaxRank< MatrixT >(), typename MatrixT::ValueType > pivots;
    _MatrixRowEchelonForm( i_matrix, pivots );
    return pivots.Size();
}

LINEAR_NS_CLOSE
