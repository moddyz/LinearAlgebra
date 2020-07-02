#pragma once

/// \file matrixEntryArray.h
///
/// Internal implementation for a fixed size array for storage of matrix indices and associated data.

#include <array>

#include <linear/linear.h>

#include <linear/base/assert.h>

LINEAR_NS_OPEN

/// \class MatrixIndex
///
/// Simple matrix index encoding of a row and column.
class MatrixIndex
{
public:
    /// Default constructor.
    inline MatrixIndex()
    {
    }

    /// Constructor with specified row and column indices.
    explicit inline MatrixIndex( size_t i_rowIndex, size_t i_columnIndex )
        : m_rowIndex( i_rowIndex )
        , m_columnIndex( i_columnIndex )
    {
    }

    /// \return the row component.
    inline size_t Row() const
    {
        return m_rowIndex;
    }

    /// \return the column component.
    inline size_t Column() const
    {
        return m_columnIndex;
    }

private:
    size_t m_rowIndex    = 0;
    size_t m_columnIndex = 0;
};

/// \class MatrixEntryArray
///
/// Fixed capacity storage of an array of matrix index and associated value.
///
/// This implementation is minimal, only to serve the needs of various internal implementation
/// details of linear algebra operations - it is <em>not intended to be used as public API</em>
template < size_t CAPACITY, typename ValueT >
class MatrixEntryArray final
{
public:
    /// \typedef ValueType
    using ValueType = ValueT;

    /// \typedef Entry
    ///
    /// Convenience typedef of each entry.
    ///
    /// An entry is described by its location in the array and its value.
    using Entry = std::tuple< MatrixIndex, ValueT >;

    /// Get the capacity (maximum number of entries which can be stored) of this array.
    inline int Capacity() const
    {
        return CAPACITY;
    }

    /// Reset the state of this array, allowing this array to be used across mutiple passes.
    void Reset()
    {
        m_entriesCount = 0;
    }

    /// Get the number of stored entries.
    inline size_t Size() const
    {
        return m_entriesCount;
    }

    /// Set the value \p i_value at (\p i_rowIndex, \p i_columnIndex) of this array.
    inline void Append( size_t i_rowIndex, size_t i_columnIndex, const ValueT& i_value )
    {
        LINEAR_ASSERT( m_entriesCount < CAPACITY );
        m_entries[ m_entriesCount++ ] = std::make_tuple( MatrixIndex( i_rowIndex, i_columnIndex ), i_value );
    }

    inline const Entry& operator[]( size_t i_index ) const
    {
        return m_entries[ i_index ];
    }

    /// Custom iterator class to enable range iteration over the entries of MatrixEntryArray.
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
        iterator operator++()
        {
            m_entry++;
            return *this;
        }

    private:
        const Entry* m_entry = nullptr;
    };

    /// \return The iterator referring to the beginning of the range of entries for forward iteration.
    iterator begin() const
    {
        return iterator( &m_entries[ 0 ] );
    }

    /// \return The iterator referring to the end of the range of entries for forward iteration.
    iterator end() const
    {
        return iterator( &m_entries[ m_entriesCount ] );
    }

private:
    /// Currently number of stored entries.
    size_t m_entriesCount = 0;

    /// Entries in this array.
    std::array< Entry, CAPACITY > m_entries;
};

LINEAR_NS_CLOSE
