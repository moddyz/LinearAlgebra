#pragma once

/// \file intRange.h
///
/// Integer range, for convenience iteration purposes.

#include <linear/base/assert.h>

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

/// \class IntRange
///
/// Convience iteration over a range of integers, with bi-directional support.
///
/// The integers in the range are \em inclusive of \p i_begin and \em exclusive  of \p i_end.
class IntRange
{
public:
    IntRange( int i_begin, int i_end )
        : m_begin( i_begin )
        , m_end( i_end )
        , m_increment( i_begin < i_end ? 1 : -1 )
    {
    }

    class iterator final
    {
    public:
        iterator( int i_current, int i_increment )
            : m_current( i_current )
            , m_increment( i_increment )
        {
        }

        /// In-equality operator, for check for iteration termination.
        bool operator!=( const iterator& i_other ) const
        {
            return m_current != i_other.m_current;
        }

        /// De-referencing operator, to get the value.
        int operator*() const
        {
            return m_current;
        }

        /// Increment the iterator.
        const iterator& operator++()
        {
            m_current += m_increment;
            return *this;
        }

    private:
        int m_current   = 0;
        int m_increment = 0;
    };

    /// \return The iterator referring to the beginning of the entries array.
    iterator begin() const
    {
        return iterator( m_begin, m_increment );
    }

    /// \return The iterator referring to the end of the entries array.
    iterator end() const
    {
        return iterator( m_end, m_increment );
    }

private:
    int m_begin     = 0;
    int m_end       = 0;
    int m_increment = 0;
};

LINEAR_ALGEBRA_NS_CLOSE

