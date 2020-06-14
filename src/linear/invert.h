#pragma once

/// \file invert.h
///
/// Matrix inversion.
///
/// Find the unique inverse matrix of \p A  such that <p>A * A^-1 = I</p> where \p I is the identity matrix.

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

/// Compute the inverse of a matrix via Gauss-Jordan elimination.
///
/// If matrix \p i_matrix is invertable, store its computed inverse in \p o_inverse.
///
/// If elimination fails due to \p i_matrix being \em singular, the value of \p o_inverse will stay un-modified.
///
/// \pre \p i_matrix must be square.
///
/// \param i_matrix the input matrix to invert.
/// \param o_inverse the output inverted matrix.
///
/// \return true if i_matrix is invertible.
inline bool Invert( const MatrixT& i_matrix, MatrixT& o_inverse )
{
    static_assert( MatrixT::RowCount() == MatrixT::RowCount() );
    // TODO.
}

LINEAR_ALGEBRA_NS_CLOSE
