#pragma once

/// \file invert.h
///
/// Matrix row echelon form.
///
/// Reducing a matrix into its row echelon form (REF) exposes its pivot & free columns.
/// This reduction is achieved through elimination.
///
/// The row echelon form has following features:
/// - zero rows are at the bottom of the matrix.
/// - each pivot is to the right of the pivot of the row above it.
///
/// A matrix in row echelon form can be further reduced into the row reduced echelon form (RREF),
/// with the addition of the following features:
/// - the co-efficient in a pivot column is 1.
/// - all the other values in a pivot column is 0.
///
/// The row reduced echelon form (RREF) of a matrix allows even easier discoverability of
/// the pivot and free columns.

#include <linear/base/matrixRowEchelon.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Compute the <em>row echelon form</em> of a matrix, through elimination.
///
/// \param i_matrix the input matrix.
///
/// \return the row echelon form of the input matrix.
template < typename MatrixT >
inline bool RowEchelonForm( const MatrixT& i_matrix )
{
    return _MatrixRowEchelonForm( i_matrix );
}

/// Compute the <em>row reduced echelon form</em> of a matrix, through elimination.
///
/// \param i_matrix the input matrix.
///
/// \return the row reduced echelon form of the input matrix.
template < typename MatrixT >
inline bool RowReducedEchelonForm( const MatrixT& i_matrix )
{
    return _MatrixRowReducedEchelonForm( i_matrix );
}

LINEAR_ALGEBRA_NS_CLOSE
