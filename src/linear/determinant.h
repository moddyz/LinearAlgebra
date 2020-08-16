#pragma once

/// \file inverse.h
/// \ingroup LinearAlgebra_Operations
///
/// Determinant computation.
///
/// The determinant of a square matrix is computed by elimination, bringing A to U, then
/// multiplying the pivots.
///
/// If the input matrix is singular, then the determinant is \p 0.  If it is non-singular, then
/// the determinant is non-zero.

#include <linear/base/matrixElimination.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_NS_OPEN

/// Compute the determinant of a matrix via the product of pivots.
/// \ingroup LinearAlgebra_Operations
///
/// \param i_matrix The matrix to compute the determinant for.
///
/// \return The determinant of \p i_matrix.
template < typename MatrixT >
inline typename MatrixT::ValueType Determinant( const MatrixT& i_matrix )
{
    static_assert( MatrixT::RowCount() == MatrixT::ColumnCount() );

    // Left-hand-side working matrix.  This will assume the identity matrix after the full Gauss-Jordan elimination.
    MatrixT matrix = i_matrix;

    // Use cache to record on i_matrix.
    MatrixEntryArray< MatrixT::RowCount(), typename MatrixT::ValueType > eliminationFactors;

    // Count the number of row exchanges.
    int numRowExchanges = 0;

    for ( int pivotIndex = 0; pivotIndex < MatrixT::RowCount() - 1; ++pivotIndex )
    {
        // Check that the current pivot is non-zero.
        if ( matrix( pivotIndex, pivotIndex ) == 0 )
        {
            // Try to find a row below with a non-zero pivot to exchange.
            int exchangedRow = _FindAndPerformRowExchange( pivotIndex, pivotIndex, matrix );
            if ( exchangedRow != -1 )
            {
                numRowExchanges++;
            }
            else
            {
                // Matrix is singular, then the determinant is 0.
                return 0;
            }
        }

        // Perform elimination.
        _RecordElimination( pivotIndex,
                            pivotIndex,
                            IntRange( pivotIndex + 1, MatrixT::RowCount() ) /* rowRange */,
                            IntRange( pivotIndex, MatrixT::ColumnCount() ) /* columnRange */,
                            eliminationFactors,
                            matrix );
    }

    // Compute product of pivots.
    typename MatrixT::ValueType determinant = matrix( 0, 0 );
    for ( int pivotIndex = 1; pivotIndex < MatrixT::RowCount(); ++pivotIndex )
    {
        determinant *= matrix( pivotIndex, pivotIndex );
    }

    // Odd # of row exchanges imparts a -1 factor.
    if ( numRowExchanges % 2 == 0 )
    {
        return determinant;
    }
    else
    {
        return -determinant;
    }
}

LINEAR_NS_CLOSE
