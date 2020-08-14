#pragma once

/// \file orthonormalize.h
/// \ingroup LinearAlgebra_Operations
///
/// Matrix orthonormalization.
///
/// The orthonormal matrix \f$Q\f$ has the following identity:
/// \code
/// Q = Q^TQ
/// \endcode
///
/// The columns of \f$Q\f$ is independent, mutually orthogonal, and all possess the length of 1.

#include <linear/matrix.h>
#include <linear/normalize.h>
#include <linear/projection.h>

LINEAR_NS_OPEN

/// Compute the orthonormal matrix of an input matrix via the <b>Gram-Schmidt</b> process.
/// \ingroup LinearAlgebra_Operations
///
/// \pre \p i_matrix must have independent columns.
///
/// \param i_matrix The input matrix.
///
/// \return Orthonormalized matrix.
template < typename MatrixT >
inline MatrixT Orthonormalize( const MatrixT& i_matrix )
{
    using ColumnT = Matrix< MatrixT::RowCount(), 1 >;

    // Normalize and set the first column.
    MatrixT orthonormal;
    orthonormal.SetColumn( 0, Normalize( i_matrix.GetColumn( 0 ) ) );

    for ( int columnIndex : IntRange( 1, MatrixT::ColumnCount() ) )
    {
        ColumnT column = i_matrix.GetColumn( columnIndex );
        for ( int projectionIndex : IntRange( 0, columnIndex ) )
        {
            ColumnT projection = Projection( column, orthonormal.GetColumn( projectionIndex ) );
            LINEAR_VERIFY( projection != ColumnT() );
            column -= projection;
        }
        orthonormal.SetColumn( columnIndex, Normalize( column ) );
    }

    return orthonormal;
}

LINEAR_NS_CLOSE
