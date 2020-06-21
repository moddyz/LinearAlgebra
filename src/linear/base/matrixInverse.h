#pragma once

/// \file matrixInverse.h
///
/// Matrix inverse implementation details.

#include <linear/base/assert.h>
#include <linear/base/intRange.h>
#include <linear/base/matrixElimination.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Compute the inverse of a matrix via Gauss-Jordan elimination.
/// If elimination fails due to \p current matrix being \em singular, the value of \p o_inverse will be un-defined.
template < typename MatrixT >
inline bool _MatrixInverse( const MatrixT& i_matrix, MatrixT& o_inverse )
{
    static_assert( MatrixT::RowCount() == MatrixT::RowCount() );

    // Left-hand-side working matrix.  This will assume the identity matrix after the full Gauss-Jordan elimination.
    MatrixT matrix = i_matrix;

    // This matrix begins as the identity, and will assume the inverse after elimiination.
    o_inverse = MatrixT::Identity();

    // Use cache to record on i_matrix and replay on o_inverse.
    EliminationCache< MatrixT::RowCount(), typename MatrixT::ValueType > eliminationCache;

    // Gauss step: E*A -> U
    for ( int pivotIndex = 0; pivotIndex < MatrixT::RowCount() - 1; ++pivotIndex )
    {
        // Check that the current pivot is non-zero.
        if ( matrix( pivotIndex, pivotIndex ) == 0 )
        {
            // Try to find a row below with a non-zero pivot to exchange.
            int exchangedRow = _FindAndPerformRowExchange( pivotIndex, pivotIndex, matrix );
            if ( exchangedRow != -1 )
            {
                RowExchange( pivotIndex, exchangedRow, o_inverse );
            }
            else
            {
                // A matrix is invertible if and only if all its columns are independent.  Failure to find a
                // row to exchange to produce a pivot means that this column is singular (it is a combination of
                // the previous columns), thus this matrix is not generally invertible.
                return false;
            }
        }

        // Record the elimination on matrix, then replay onto o_inverse.
        _RecordElimination( pivotIndex,
                            pivotIndex,
                            IntRange( pivotIndex + 1, MatrixT::RowCount() ) /* rowRange */,
                            IntRange( pivotIndex, MatrixT::ColumnCount() ) /* columnRange */,
                            eliminationCache,
                            matrix );
        _ReplayElimination( pivotIndex,
                            pivotIndex,
                            /* columnRange */ IntRange( 0, MatrixT::ColumnCount() ),
                            eliminationCache,
                            o_inverse );

        // Reset the cache for the next iteration.
        eliminationCache.Reset();
    }

    // Jordan Step step: U*E -> D
    for ( int pivotIndex = MatrixT::RowCount() - 1; pivotIndex > 0; --pivotIndex )
    {
        // Record the elimination on matrix, then replay onto o_inverse.
        _RecordElimination( pivotIndex,
                            pivotIndex,
                            IntRange( pivotIndex - 1, -1 ) /* rowRange */,
                            IntRange( pivotIndex, -1 ) /* columnRange */,
                            eliminationCache,
                            matrix );
        _ReplayElimination( pivotIndex,
                            pivotIndex,
                            /* columnRange */ IntRange( MatrixT::ColumnCount() - 1, -1 ),
                            eliminationCache,
                            o_inverse );

        // Reset the cache for the next iteration.
        eliminationCache.Reset();
    }

    // Divide rows by diagonal pivot values.
    for ( int pivotIndex = 0; pivotIndex < MatrixT::RowCount(); ++pivotIndex )
    {
        typename MatrixT::ValueType& pivotValue        = matrix( pivotIndex, pivotIndex );
        typename MatrixT::ValueType  pivotValueInverse = 1.0 / pivotValue;
        for ( int columnIndex = 0; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
        {
            o_inverse( pivotIndex, columnIndex ) *= pivotValueInverse;
        }
    }

    // Successful inversion.
    return true;
}

LINEAR_ALGEBRA_NS_CLOSE
