#pragma once

/// \file projection.h
/// \ingroup LinearAlgebra_Operations
///
/// Projection
///
/// The projection \f$p\f$ of a vector \f$b\f$ onto a subspace S (spanned by the column-space of matrix \f$A\f$)
/// is defined as follows:
/// \f[
/// p = A(A^TA)^-1A^Tb
/// \f]
///
/// The projection matrix \f$P\f$ transforms \f$b\f$ to \f$p\f$:
/// \f[
/// p = Pb
/// P = A(A^TA)^-1A^T
/// \f]

#include <linear/inverse.h>
#include <linear/linear.h>
#include <linear/matrix.h>
#include <linear/multiply.h>
#include <linear/transpose.h>

LINEAR_NS_OPEN

/// Compute the projection matrix of a subspace, spanned by the column-space of input matrix \p i_matrix.
/// \ingroup LinearAlgebra_Operations
///
/// \param i_matrix The matrix whose column-space spans the sub-space to project onto.
///
/// \return The projection matrix.
template < typename MatrixT >
inline Matrix< MatrixT::RowCount(), MatrixT::RowCount(), typename MatrixT::ValueType >
ProjectionMatrix( const MatrixT& i_matrix )
{
    // A Transpose
    using TransposeMatrixT      = Matrix< MatrixT::ColumnCount(), MatrixT::RowCount(), typename MatrixT::ValueType >;
    TransposeMatrixT aTranspose = Transpose( i_matrix );

    // A^T * A term.
    using ATAMatrixT       = Matrix< MatrixT::ColumnCount(), MatrixT::ColumnCount(), typename MatrixT::ValueType >;
    ATAMatrixT aTransposeA = Multiply( aTranspose, i_matrix );

    // (A^T * A)^-1
    ATAMatrixT aTransposeAInverse;
    LINEAR_VERIFY( Inverse( aTransposeA, aTransposeAInverse ) );

    // A * (A^T * A)^-1 * A^T
    return Multiply( Multiply( i_matrix, aTransposeAInverse ), aTranspose );
}

/// Compute the projection of a vector onto a subspace.
/// \ingroup LinearAlgebra_Operations
///
/// \param i_vector The column vector to project onto the sub-space.
/// \param i_matrix The matrix whose column-space spans the sub-space to project onto.
///
/// \return \p true if i_matrix is invertible. \p false if \p i_matrix is singular (thus cannot be inverted).
template < typename VectorT, typename MatrixT >
inline VectorT Projection( const VectorT& i_vector, const MatrixT& i_matrix )
{
    return Multiply( ProjectionMatrix( i_matrix ), i_vector );
}

LINEAR_NS_CLOSE
