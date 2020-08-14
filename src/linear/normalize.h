#pragma once

/// \file multiply.h
/// \ingroup LinearAlgebra_Operations
///
/// Vector normalization.
///
/// Only applicable for matrices with a column count of 1 (a column vector).
///
/// Divide each component by its length.

#include <linear/matrix.h>
#include <linear/multiply.h>
#include <linear/transpose.h>

LINEAR_NS_OPEN

/// Compute the normalized version of a column vector vector.
/// \ingroup LinearAlgebra_Operations
///
/// \param i_columnVector The column vector.
///
/// \return The normalized column vector.
template < typename MatrixT >
constexpr inline MatrixT Normalize( const MatrixT& i_columnVector )
{
    static_assert( MatrixT::ColumnCount() == 1 );
    LINEAR_ASSERT( Multiply( Transpose( i_columnVector ), i_columnVector )[ 0 ] != 0 );
    return i_columnVector / ( float ) sqrt( Multiply( Transpose( i_columnVector ), i_columnVector )[ 0 ] );
}

LINEAR_NS_CLOSE
