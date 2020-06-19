#pragma once

/// \file matrixInverse.h
///
/// Matrix inverse implementation details.

#include <linear/base/assert.h>
#include <linear/base/matrixElimination.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Performs an elimination step by subtracting the pivot row from all the rows above, to \em zero out
/// the column above the pivot!
template < typename MatrixT >
inline bool _JordanEliminationStep( int i_pivotIndex, MatrixT& o_matrix, MatrixT& o_inverse )
{
    // Double check pivot.
    LINEAR_ALGEBRA_ASSERT( o_matrix( i_pivotIndex, i_pivotIndex ) != 0 );

    // Store the pivotValue for usage throughout the elimination for this column.
    const typename MatrixT::ValueType pivotValue = o_matrix( i_pivotIndex, i_pivotIndex );

    // Cache the pivot rowss
    Matrix< 1, MatrixT::ColumnCount() > pivotRow        = GetRow( o_matrix, i_pivotIndex );
    Matrix< 1, MatrixT::ColumnCount() > inversePivotRow = GetRow( o_inverse, i_pivotIndex );

    // For each row below the pivot, try eliminate each (rowIndex, i_pivotIndex) entry by subtracting the pivot row
    // multiplied by an elimination factor from that row.
    for ( int rowIndex = i_pivotIndex - 1; rowIndex >= 0; rowIndex-- )
    {
        typename MatrixT::ValueType targetValue = o_matrix( rowIndex, i_pivotIndex );
        if ( targetValue != 0 )
        {
            // Compute the elimination factor.
            typename MatrixT::ValueType eliminationFactor = targetValue / pivotValue;

            // Eliminate the row of o_matrix.
            Matrix< 1, MatrixT::ColumnCount() > eliminationRow = pivotRow * eliminationFactor;
            for ( int columnIndex = i_pivotIndex; columnIndex >= 0; columnIndex-- )
            {
                o_matrix( rowIndex, columnIndex ) -= eliminationRow( 0, columnIndex );
            }

            // Eliminate the row of o_inverse.
            Matrix< 1, MatrixT::ColumnCount() > inverseEliminationRow = inversePivotRow * eliminationFactor;
            for ( int columnIndex = MatrixT::ColumnCount() - 1; columnIndex >= 0; columnIndex-- )
            {
                o_inverse( rowIndex, columnIndex ) -= inverseEliminationRow( 0, columnIndex );
            }
        }
    }

    return false;
}

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
            int exchangedRow = _FindAndPerformRowExchange( pivotIndex, matrix );
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
        _RecordEliminationBelowPivot( pivotIndex, eliminationCache, matrix );
        _ReplayEliminationBelowPivot( pivotIndex, eliminationCache, o_inverse );

        // Reset the cache for the next iteration.
        eliminationCache.Reset();
    }

    // Jordan Step step: U*E -> D
    for ( int pivotIndex = MatrixT::RowCount() - 1; pivotIndex > 0; --pivotIndex )
    {
        _JordanEliminationStep( pivotIndex, matrix, o_inverse );
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
