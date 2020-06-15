#pragma once

/// \file matrixInverse.h
///
/// Matrix inverse implenmentation details.
///
/// Find the unique inverse matrix of \p A  such that <p>A * A^-1 = I</p> where \p I is the identity matrix.

#include <linear/base/assert.h>
#include <linear/linear.h>
#include <linear/matrix.h>
#include <linear/row.h>
#include <linear/slice.h>

LINEAR_ALGEBRA_NS_OPEN

template < typename MatrixT >
inline bool _GaussEliminationStep( size_t i_pivotIndex, MatrixT& o_matrix, MatrixT& o_inverseTransition )
{
    // Double check pivot.
    LINEAR_ALGEBRA_ASSERT( o_matrix( i_pivotIndex, i_pivotIndex ) != 0 );

    // Store the pivotValue for usage throughout the elimination for this column.
    const typename MatrixT::ValueType pivotValue = o_matrix( i_pivotIndex, i_pivotIndex );

    // Cache the pivot rowss
    Matrix< 1, MatrixT::ColumnCount() > pivotRow =
        Slice< i_pivotIndex, 0, i_pivotIndex + 1, MatrixT::ColumnCount() >( o_matrix );
    Matrix< 1, MatrixT::ColumnCount() > inversePivotRow =
        Slice< i_pivotIndex, 0, i_pivotIndex + 1, MatrixT::ColumnCount() >( o_inverseTransition );

    // For each row below the pivot, try eliminate each (rowIndex, i_pivotIndex) entry by subtracting the pivot row
    // multiplied by an elimination factor from that row.
    for ( size_t rowIndex = i_pivotIndex + 1; rowIndex < MatrixT::RowCount(); rowIndex++ )
    {
        typename MatrixT::ValueType targetValue = o_matrix( rowIndex, i_pivotIndex );
        if ( targetValue != 0 )
        {
            // Compute the elimination factor.
            typename MatrixT::ValueType eliminationFactor = targetValue / pivotValue;

            // Eliminate the row of o_matrix.
            Matrix< 1, MatrixT::ColumnCount() > eliminationRow = pivotRow * eliminationFactor;
            for ( size_t columnIndex = i_pivotIndex; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
            {
                o_matrix( rowIndex, columnIndex ) -= eliminationRow( 0, columnIndex );
            }

            // Eliminate the row of o_inverseTransition.
            Matrix< 1, MatrixT::ColumnCount() > inverseEliminationRow = inversePivotRow * eliminationFactor;
            for ( size_t columnIndex = i_pivotIndex; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
            {
                o_inverseTransition( rowIndex, columnIndex ) -= inverseEliminationRow( 0, columnIndex );
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
inline bool _FindAndPerformRowExchange( size_t i_pivotIndex, MatrixT& o_matrix )
{
    // Double check ourselves.
    LINEAR_ALGEBRA_ASSERT( o_matrix( i_pivotIndex, i_pivotIndex ) == 0 );

    for ( size_t rowIndex = i_pivotIndex + 1; rowIndex < MatrixT::RowCount(); ++rowIndex )
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

    // Gauss step: E*A -> LU
    for ( size_t pivotIndex = 0; pivotIndex < MatrixT::RowCount(); ++pivotIndex )
    {
        // Check that the current pivot is non-zero.  If it is zero perform a row exchange.
        if ( matrix( pivotIndex, pivotIndex ) == 0 && !_FindAndPerformRowExchange( pivotIndex, matrix ) )
        {
            return false;
        }

        _GaussEliminationStep( pivotIndex, matrix, o_inverse );
    }

    // Jordan step.

    // Successful inversion.
    return true;
}

LINEAR_ALGEBRA_NS_CLOSE
