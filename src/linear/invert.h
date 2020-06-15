#pragma once

/// \file invert.h
///
/// Matrix inversion API.

#include <linear/base/matrixInverse.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Compute the inverse of a matrix via Gauss-Jordan elimination.
///
/// If matrix \p current matrix is invertable, store its computed inverse in \p o_inverse.
///
/// \pre The current matrix must be square.
///
/// \param o_inverse the output inverted matrix.
///
/// \return \p true if i_matrix is invertible. \p false if \p i_matrix is singular (thus cannot be inverted).
template < typename MatrixT >
inline bool Invert( const MatrixT& i_matrix, MatrixT& o_inverse )
{
    return _MatrixInverse( i_matrix, o_inverse );
}

LINEAR_ALGEBRA_NS_CLOSE
