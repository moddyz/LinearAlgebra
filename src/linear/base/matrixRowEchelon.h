#pragma once

/// \file matrixRowEchelon.h
///
/// Matrix row echelon reduction implementation details.

#include <linear/linear.h>

#include <linear/base/assert.h>
#include <linear/base/intRange.h>
#include <linear/base/matrixElimination.h>
#include <linear/base/matrixEntryArray.h>

#include <linear/matrix.h>

#include <iostream>

LINEAR_NS_OPEN

/// Compute the row echelon form of \p i_matrix, storing the kinds of columns revealed throughout the
/// reduction process so that it can accelerate a calling operation like _MatrixReducedRowEchelonForm,
/// or to find out the rank of a matrix.
template < typename MatrixT >
inline MatrixT _MatrixRowEchelonForm(
    const MatrixT&                                                                                            i_matrix,
    MatrixEntryArray< std::min( MatrixT::RowCount(), MatrixT::ColumnCount() ), typename MatrixT::ValueType >& o_pivots )
{
    // Working matrix copy.
    MatrixT matrix = i_matrix;

    // Record elimination operations.
    MatrixEntryArray< MatrixT::RowCount(), typename MatrixT::ValueType > eliminationFactors;

    // Elimination, reducing matrix A into U (upper triangular).
    int pivotRowIndex = 0, pivotColIndex = 0;
    while ( pivotRowIndex < MatrixT::RowCount() && pivotColIndex < MatrixT::ColumnCount() )
    {
        const typename MatrixT::ValueType& pivotValue = matrix( pivotRowIndex, pivotColIndex );
        if ( matrix( pivotRowIndex, pivotColIndex ) == 0 )
        {
            // Try to find a row below with a non-zero pivot to exchange.
            int exchangedRow = _FindAndPerformRowExchange( pivotRowIndex, pivotColIndex, matrix );
            if ( exchangedRow == -1 )
            {
                // Only increment column index and continue with elimination.
                pivotColIndex += 1;
                continue;
            }
        }

        // Record the elimination on matrix, then replay onto o_inverse.
        _RecordElimination( pivotRowIndex,
                            pivotColIndex,
                            IntRange( pivotRowIndex + 1, MatrixT::RowCount() ) /* rowRange */,
                            IntRange( pivotColIndex, MatrixT::ColumnCount() ) /* columnRange */,
                            eliminationFactors,
                            matrix );

        eliminationFactors.Reset();

        // This column has a pivot.
        o_pivots.Append( pivotRowIndex, pivotColIndex, pivotValue );

        // Increment both pivot row & column indices.
        pivotRowIndex += 1;
        pivotColIndex += 1;
    }

    return matrix;
}

/// Compute the reduced row echelon form of \p i_matrix.
template < typename MatrixT >
inline MatrixT _MatrixReducedRowEchelonForm( const MatrixT& i_matrix )
{
    using PivotsT =
        MatrixEntryArray< std::min( MatrixT::RowCount(), MatrixT::ColumnCount() ), typename MatrixT::ValueType >;
    PivotsT pivots;
    MatrixT rowEchelonForm = _MatrixRowEchelonForm( i_matrix, pivots );

    // Record elimination operations.
    MatrixEntryArray< MatrixT::RowCount(), typename MatrixT::ValueType > eliminationFactors;

    // The
    for ( int entryIndex : IntRange( pivots.Size() - 1, -1 ) )
    {
        const typename PivotsT::Entry& entry      = pivots[ entryIndex ];
        const MatrixIndex&             pivotIndex = std::get< 0 >( entry );

        // Perform elimination, by subtracting the pivot's row from the rows above, to
        // zero out their co-efficients in the pivot's column.
        _RecordElimination( pivotIndex.Row(),
                            pivotIndex.Column(),
                            IntRange( pivotIndex.Row() - 1, -1 ) /* rowRange */,
                            IntRange( MatrixT::ColumnCount() - 1, -1 ) /* columnRange */,
                            eliminationFactors,
                            rowEchelonForm );

        // Divide the pivot row by the pivot value, so that it becomes 1.
        const typename PivotsT::ValueType& pivotValue        = std::get< 1 >( entry );
        typename MatrixT::ValueType        pivotValueInverse = 1.0 / pivotValue;
        for ( int columnIndex = 0; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
        {
            rowEchelonForm( pivotIndex.Row(), columnIndex ) *= pivotValueInverse;
        }

        eliminationFactors.Reset();
    }

    return rowEchelonForm;
}

LINEAR_NS_CLOSE
