#pragma once

/// \file matrixElimination.h
///
/// Common matrix elimination sub-routines.

#include <linear/base/diagnostic.h>
#include <linear/base/intRange.h>
#include <linear/base/matrixEntryArray.h>

#include <linear/linear.h>
#include <linear/matrix.h>
#include <linear/row.h>

LINEAR_NS_OPEN

/// Find a row \em below row \p i_pivotRowIndex in matrix \p o_matrix such that its co-efficient
/// (at \p i_pivotColIndex) is not 0, then exchange it with the pivot row.
///
/// \return a positive integer if a viable row is found.  Otherwise, \p -1.
template < typename MatrixT >
inline int _FindAndPerformRowExchange( int i_pivotRowIndex, int i_pivotColIndex, MatrixT& o_matrix )
{
    // Double check that value at the current pivot is 0 (which is why a row-exchange is required in the first place!)
    LINEAR_ASSERT( o_matrix( i_pivotRowIndex, i_pivotColIndex ) == 0 );

    for ( int rowIndex = i_pivotRowIndex + 1; rowIndex < MatrixT::RowCount(); ++rowIndex )
    {
        if ( o_matrix( rowIndex, i_pivotColIndex ) != 0 )
        {
            RowExchange( rowIndex, i_pivotRowIndex, o_matrix );
            return rowIndex;
        }
    }

    return -1;
}
/// Performs an elimination step by subtracting the pivot row from all the rows below with a non-zero co-efficient,
/// to \em zero them out.
///
/// \p o_eliminationFactors is populated with the eliminated row indices and the corresponding factors.
///
/// Allowing the recording of the elimination factors at the respective rows allow the same operations to be efficiently
/// replayed and performed on another matrix.
template < typename MatrixT >
inline void
_RecordElimination( int                                                                   i_pivotRowIndex,
                    int                                                                   i_pivotColIndex,
                    const IntRange&                                                       i_rowRange,
                    const IntRange&                                                       i_columnRange,
                    MatrixEntryArray< MatrixT::RowCount(), typename MatrixT::ValueType >& o_eliminationFactors,
                    MatrixT&                                                              o_matrix )
{
    // Double check pivot.
    LINEAR_ASSERT( o_matrix( i_pivotRowIndex, i_pivotColIndex ) != 0 );

    // Store the reciprocal of the pivot co-efficient for usage throughout this elimination step.
    const typename MatrixT::ValueType pivotValueReciprocal = 1.0 / o_matrix( i_pivotRowIndex, i_pivotColIndex );

    // Cache the pivot row.
    Matrix< 1, MatrixT::ColumnCount() > pivotRow = GetRow( o_matrix, i_pivotRowIndex );

    // For each row below the pivot, try to eliminate any non-zero co-efficients.
    for ( int rowIndex : i_rowRange )
    {
        typename MatrixT::ValueType targetValue = o_matrix( rowIndex, i_pivotColIndex );
        if ( targetValue != 0 )
        {
            // Compute the elimination factor.
            typename MatrixT::ValueType eliminationFactor = targetValue * pivotValueReciprocal;

            // Eliminate a co-efficient.
            Matrix< 1, MatrixT::ColumnCount() > eliminationRow = pivotRow * eliminationFactor;
            for ( int columnIndex : i_columnRange )
            {
                o_matrix( rowIndex, columnIndex ) -= eliminationRow( 0, columnIndex );
            }

            // Cache the row index and factor for replay-ability on another matrix.
            o_eliminationFactors.Append( rowIndex, i_pivotColIndex, eliminationFactor );
        }
    }
}

/// Performs an elimination step by subtracting the pivot row from all the rows below, to \em zero out
/// the co-efficients under the pivot, using by replaying the cache entries from \p i_eliminationFactors.
template < typename MatrixT >
inline void
_ReplayElimination( int                                                                         i_pivotRowIndex,
                    int                                                                         i_pivotColIndex,
                    const IntRange&                                                             i_columnRange,
                    const MatrixEntryArray< MatrixT::RowCount(), typename MatrixT::ValueType >& i_eliminationFactors,
                    MatrixT&                                                                    o_matrix )
{
    using MatrixEntryArrayT = MatrixEntryArray< MatrixT::RowCount(), typename MatrixT::ValueType >;

    // Cache the pivot row.
    Matrix< 1, MatrixT::ColumnCount() > pivotRow = GetRow( o_matrix, i_pivotRowIndex );

    // Replay the cache and apply elimination
    for ( const typename MatrixEntryArrayT::Entry& entry : i_eliminationFactors )
    {
        // Pull cache values.
        const MatrixIndex&                           eliminationIndex  = std::get< 0 >( entry );
        const typename MatrixEntryArrayT::ValueType& eliminationFactor = std::get< 1 >( entry );

        // Perform elimination on target row.
        Matrix< 1, MatrixT::ColumnCount() > eliminationRow = pivotRow * eliminationFactor;
        for ( int columnIndex : i_columnRange )
        {
            o_matrix( eliminationIndex.Row(), columnIndex ) -= eliminationRow( 0, columnIndex );
        }
    }
}

LINEAR_NS_CLOSE
