#pragma once

/// \file matrixElimination.h
///
/// Common matrix elimination sub-routines.

#include <linear/base/assert.h>

#include <linear/linear.h>
#include <linear/matrix.h>
#include <linear/row.h>

LINEAR_ALGEBRA_NS_OPEN

/// Find a row \em below row \p i_pivotIndex in matrix \p o_matrix such that its co-efficient (in the same column)
/// is not 0, then exchange it with the pivot row.
///
/// \return a positive integer if a viable row is found.  Otherwise, \p -1.
template < typename MatrixT >
inline int _FindAndPerformRowExchange( int i_pivotIndex, MatrixT& o_matrix )
{
    // Double check that value at the current pivot is 0 (which is why a row-exchange is required in the first place!)
    LINEAR_ALGEBRA_ASSERT( o_matrix( i_pivotIndex, i_pivotIndex ) == 0 );

    for ( int rowIndex = i_pivotIndex + 1; rowIndex < MatrixT::RowCount(); ++rowIndex )
    {
        if ( o_matrix( rowIndex, i_pivotIndex ) != 0 )
        {
            RowExchange( rowIndex, i_pivotIndex, o_matrix );
            return rowIndex;
        }
    }

    return -1;
}

/// \class EliminationCache
///
/// Cache the row indices and corresponding elimination factors from a elimination step performed for a pivot.
/// This is so that the operation can be replayed onto another matrix.
///
/// EliminationCache is essentially an more efficient encoding of an elimination matrix, but replaying the operations
/// encoded in this cache is more efficient than matrix multiplication (E*A) due to the number of no-op operations for
/// potentially a large number of zero co-efficients.
///
/// A possible alternative is encoding the elimination co-efficients in a sparse matrix, which would require support
/// for sparse matrix multiplication (for another day).
template < size_t ROWS, typename ValueT >
class EliminationCache final
{
public:
    /// \typedef ValueType
    using ValueType = ValueT;

    /// An entry of the cache stores the row index and the corresponding elimination factor.
    using Entry = std::tuple< size_t, ValueT >;

    constexpr EliminationCache()
    {
    }

    /// Reset the state of the elimination cache.
    /// This is so this cache can be re-used, and for the possibility of stack allocation.
    void Reset()
    {
        m_entriesCount = 0;
    }

    /// Append a new entry to the cache.
    void Append( size_t i_rowIndex, ValueT i_value )
    {
        LINEAR_ALGEBRA_ASSERT( i_rowIndex < ROWS );
        LINEAR_ALGEBRA_ASSERT( m_entriesCount < ROWS );
        m_entries[ m_entriesCount++ ] = Entry( i_rowIndex, i_value );
    }

    /// Custom iterator class to enable iteration over the entries of a EliminationCache.
    class iterator final
    {
    public:
        /// Iterator constructor.
        iterator( const Entry* i_entry )
            : m_entry( i_entry )
        {
        }

        /// In-equality operator, for check for iteration termination.
        bool operator!=( const iterator& i_other ) const
        {
            return m_entry != i_other.m_entry;
        }

        /// De-referencing operator, to get the value.
        const Entry& operator*() const
        {
            return *m_entry;
        }

        /// Increment the iterator.
        const iterator& operator++()
        {
            m_entry++;
            return *this;
        }

    private:
        const Entry* m_entry = nullptr;
    };

    /// \return The iterator referring to the beginning of the entries array.
    iterator begin() const
    {
        return iterator( &m_entries[ 0 ] );
    }

    /// \return The iterator referring to the end of the entries array.
    iterator end() const
    {
        return iterator( &m_entries[ m_entriesCount ] );
    }

private:
    size_t m_entriesCount = 0;
    Entry  m_entries[ ROWS ];
};

/// Performs an elimination step by subtracting the pivot row from all the rows below, to \em zero out
/// the co-efficients under the pivot!
///
/// \p o_eliminationCache is populated with the eliminated row indices and the corresponding factors.
///
/// Allowing the recording of the elimination factors at the respective rows allow the same operations to be efficiently
/// replayed and performed on another matrix.
template < typename MatrixT >
inline void
_RecordEliminationBelowPivot( int                                                                   i_pivotIndex,
                              EliminationCache< MatrixT::RowCount(), typename MatrixT::ValueType >& o_eliminationCache,
                              MatrixT&                                                              o_matrix )
{
    // Double check pivot.
    LINEAR_ALGEBRA_ASSERT( o_matrix( i_pivotIndex, i_pivotIndex ) != 0 );

    // Store the reciprocal of the pivot co-efficient for usage throughout this elimination step.
    const typename MatrixT::ValueType pivotValueReciprocal = 1.0 / o_matrix( i_pivotIndex, i_pivotIndex );

    // Cache the pivot row.
    Matrix< 1, MatrixT::ColumnCount() > pivotRow = GetRow( o_matrix, i_pivotIndex );

    // For each row below the pivot, try to eliminate any non-zero co-efficients in the
    for ( int rowIndex = i_pivotIndex + 1; rowIndex < MatrixT::RowCount(); rowIndex++ )
    {
        typename MatrixT::ValueType targetValue = o_matrix( rowIndex, i_pivotIndex );
        if ( targetValue != 0 )
        {
            // Compute the elimination factor.
            typename MatrixT::ValueType eliminationFactor = targetValue * pivotValueReciprocal;

            // Cache the row index and factor for replayability on another matrix.
            o_eliminationCache.Append( rowIndex, eliminationFactor );

            // Eliminate a co-efficient.
            Matrix< 1, MatrixT::ColumnCount() > eliminationRow = pivotRow * eliminationFactor;
            for ( int columnIndex = i_pivotIndex; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
            {
                o_matrix( rowIndex, columnIndex ) -= eliminationRow( 0, columnIndex );
            }
        }
    }
}

/// Performs an elimination step by subtracting the pivot row from all the rows below, to \em zero out
/// the co-efficients under the pivot, using by replaying the cache entries from \p i_eliminationCache.
template < typename MatrixT >
inline void _ReplayEliminationBelowPivot(
    int                                                                         i_pivotIndex,
    const EliminationCache< MatrixT::RowCount(), typename MatrixT::ValueType >& i_eliminationCache,
    MatrixT&                                                                    o_matrix )
{
    using EliminationCacheT = EliminationCache< MatrixT::RowCount(), typename MatrixT::ValueType >;

    // Cache the pivot row.
    Matrix< 1, MatrixT::ColumnCount() > pivotRow = GetRow( o_matrix, i_pivotIndex );

    // Replay the cache and apply elimination
    for ( const typename EliminationCacheT::Entry& entry : i_eliminationCache )
    {
        // Pull cache values.
        const size_t                                 rowIndex          = std::get< 0 >( entry );
        const typename EliminationCacheT::ValueType& eliminationFactor = std::get< 1 >( entry );

        // Perform elimination on target row.
        Matrix< 1, MatrixT::ColumnCount() > eliminationRow = pivotRow * eliminationFactor;
        for ( int columnIndex = 0; columnIndex < MatrixT::ColumnCount(); columnIndex++ )
        {
            o_matrix( rowIndex, columnIndex ) -= eliminationRow( 0, columnIndex );
        }
    }
}


LINEAR_ALGEBRA_NS_CLOSE
