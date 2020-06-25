#pragma once

/// \file rank.h
///
/// Matrix rank.
///
/// The \em rank of a matrix is the number of pivot columns it possesses, or in other words,
/// the number of independent columns.

#include <linear/linear.h>

LINEAR_NS_OPEN

/// Compute the \em maximum rank a matrix of type \p MatrixT can have.
///
/// \return the maximum rank.
template < typename MatrixT >
constexpr inline size_t MaxRank()
{
    return std::min( MatrixT::RowCount(), MatrixT::ColumnCount() );
}

LINEAR_NS_CLOSE
