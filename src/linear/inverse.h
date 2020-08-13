#pragma once

/// \file inverse.h
/// \ingroup LinearAlgebra_Operations
///
/// Matrix inversion.
///
/// The inverse matrix of \p A is the unique matrix such that
/// \code
/// A * A^-1 = I
/// \endcode
/// where \p I is the identity matrix.

#include <linear/base/matrixInverse.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_NS_OPEN

/// Compute the inverse of a matrix via <b>Gauss-Jordan Elimination</b>.
/// \ingroup LinearAlgebra_Operations
///
/// If matrix \p i_matrix is invertible, store its computed inverse in \p o_inverse.
///
/// \pre The matrix \p i_matrix must be square.
///
/// \param o_inverse the output inverted matrix.
///
/// \return \p true if i_matrix is invertible. \p false if \p i_matrix is singular (thus cannot be inverted).
template < typename MatrixT >
inline bool Inverse( const MatrixT& i_matrix, MatrixT& o_inverse )
{
    return _MatrixInverse( i_matrix, o_inverse );
}

LINEAR_NS_CLOSE
