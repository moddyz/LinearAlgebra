#pragma once

/// \file matrixInverse.h
///
/// Matrix inverse implementation details.

#include <linear/base/assert.h>

#include <linear/linear.h>
#include <linear/matrix.h>
#include <linear/row.h>

#include <iostream>

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

/// Performs an elimination step by subtracting the pivot row from all the rows below, to \em zero out
/// the column under the pivot!
template < typename MatrixT >
inline bool _GaussEliminationStep( int i_pivotIndex, MatrixT& o_matrix, MatrixT& o_inverse )
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
    for ( int rowIndex = i_pivotIndex + 1; rowIndex < MatrixT::RowCount(); rowIndex++ )
    {
        typename MatrixT::ValueType targetValue = o_matrix( rowIndex, i_pivotIndex );
        if ( targetValue != 0 )
        {
            // Compute the elimination factor.
            typename MatrixT::ValueType eliminationFactor = targetValue / pivotValue;

            // Eliminate the row of o_matrix.
            Matrix< 1, MatrixT::ColumnCount() > eliminationRow = pivotRow * eliminationFactor;
            for ( int columnIndex = i_pivotIndex; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
            {
                o_matrix( rowIndex, columnIndex ) -= eliminationRow( 0, columnIndex );
            }

            // Eliminate the row of o_inverse.
            Matrix< 1, MatrixT::ColumnCount() > inverseEliminationRow = inversePivotRow * eliminationFactor;
            for ( int columnIndex = 0; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
            {
                o_inverse( rowIndex, columnIndex ) -= inverseEliminationRow( 0, columnIndex );
            }
        }
    }

    return false;
}

/// Find a row in matrix \p o_matrix where the entry (row, pivotIndex) is not 0, then exchange it with the current pivot
/// row.
///
/// \return \p true if a viable row is found.  Otherwise, \p false.
template < typename MatrixT >
inline bool _FindAndPerformRowExchange( int i_pivotIndex, MatrixT& o_matrix )
{
    // Double check ourselves.
    LINEAR_ALGEBRA_ASSERT( o_matrix( i_pivotIndex, i_pivotIndex ) == 0 );

    for ( int rowIndex = i_pivotIndex + 1; rowIndex < MatrixT::RowCount(); ++rowIndex )
    {
        if ( o_matrix( rowIndex, i_pivotIndex ) != 0 )
        {
            RowExchange( rowIndex, i_pivotIndex, o_matrix );
            return true;
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

    // Gauss step: E*A -> U
    for ( int pivotIndex = 0; pivotIndex < MatrixT::RowCount() - 1; ++pivotIndex )
    {
        // Check that the current pivot is non-zero.  If it is zero perform a row exchange.
        if ( matrix( pivotIndex, pivotIndex ) == 0 && !_FindAndPerformRowExchange( pivotIndex, matrix ) )
        {
            return false;
        }

        _GaussEliminationStep( pivotIndex, matrix, o_inverse );
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
