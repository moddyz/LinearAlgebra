#pragma once

/// \file matrixRowEchelon.h
///
/// Matrix row echelon reduction implementation details.

#include <linear/base/assert.h>
#include <linear/base/intRange.h>
#include <linear/base/matrixElimination.h>

#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// \enum ColumnType
///
/// Describes the type of column, revealed through a row echelon reduction operation.
enum ColumnType
{
    /// Pivot column type, indicating that this column <em>is not</em> a combination of its previous columns,
    /// or in other words, independent.
    ColumnType_Pivot = 0,

    /// Free column type, indicating that this column \em is a combination of its previous columns, and will
    /// produce a special \b nullspace solution.
    ColumnType_Free = 1
};

/// Compute the row echelon form of \p i_matrix, storing the kinds of columns revealed throughout the
/// reduction process so that it can accelerate a calling operation like _MatrixReducedRowEchelonForm,
/// or to find out the rank of a matrix.
template < typename MatrixT >
inline MatrixT _MatrixRowEchelonForm( const MatrixT&                                    i_matrix,
                                      std::array< ColumnType, MatrixT::ColumnCount() >& o_columnType )
{
    // Working matrix copy.
    MatrixT matrix = i_matrix;

    // Record elimination operations.
    EliminationCache< MatrixT::RowCount(), typename MatrixT::ValueType > eliminationCache;

    // Elimination, reducing matrix A into U (upper triangular).
    int pivotRowIndex = 0, pivotColIndex = 0;
    while ( pivotRowIndex < MatrixT::RowCount() && pivotColIndex < MatrixT::ColumnCount() )
    {
        if ( matrix( pivotRowIndex, pivotColIndex ) == 0 )
        {
            // Try to find a row below with a non-zero pivot to exchange.
            int exchangedRow = _FindAndPerformRowExchange( pivotRowIndex, pivotColIndex, matrix );
            if ( exchangedRow == -1 )
            {
                // Failed to find row with non-zero co-efficient.
                // This column has no pivot so is marked as a "free" column.
                o_columnType[ pivotColIndex ] = ColumnType_Free;

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
                            eliminationCache,
                            matrix );

        eliminationCache.Reset();

        // This column has a pivot.
        o_columnType[ pivotColIndex ] = ColumnType_Pivot;

        // Increment both pivot row & column indices.
        pivotRowIndex += 1;
        pivotColIndex += 1;
    }

    return matrix;
}

LINEAR_ALGEBRA_NS_CLOSE
