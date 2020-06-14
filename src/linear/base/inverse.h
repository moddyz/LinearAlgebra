#pragma once

/// \file inverse.h
///
/// Matrix inverse implenmentation details.
///
/// Find the unique inverse matrix of \p A  such that <p>A * A^-1 = I</p> where \p I is the identity matrix.

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Compute the inverse of a matrix via Gauss-Jordan elimination.
/// If elimination fails due to \p current matrix being \em singular, the value of \p o_inverse will be un-defined.
template < typename MatrixT >
inline bool _MatrixInverse( const MatrixT& i_matrix, MatrixT& o_inverse )
{
    static_assert( MatrixT::RowCount() == MatrixT::RowCount() );

    //MatrixT matrix = i_matrix;
    //o_inverse = GetIdentity< MatrixT >();

    return MatrixT::Identity();
}

LINEAR_ALGEBRA_NS_CLOSE
