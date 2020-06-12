#pragma once

/// \file matrix.h
///
/// A matrix is rectangular array of numbers, arranged in to rows and columns (M x N).

#include <linearAlgebra/linearAlgebra.h>

LINEAR_ALGEBRA_NS_OPEN

/// \class Matrix
///
/// Class representing a compile-time defined M x N matrix.
///
/// Templatizing the number of rows and columns allow the memory of the matrix
/// to be allocated on the stack, instead of the heap.  This is great for
/// applications with well-defined input and output parameters.
///
/// \tparam ElementType value type of the elements.
/// \tparam M number of rows in this matrix.
/// \tparam N number of columns in this matrix.
template < size_t M, size_t N, typename ElementT = float >
class Matrix
{
public:
    /// \typedef ElementType typedef for the value type of the element(s).
    typedef ElementT ElementType;

    /// Default constructor, initializing elements to \em all zeroes.
    Matrix()
    {
    }

    /// Get the row size of this matrix.
    static inline constexpr int GetRowSize()
    {
        return M;
    }

    /// Get the column size of this matrix.
    static inline constexpr int GetColumnSize()
    {
        return N;
    }

    /// Matrix element read-access by row & column.
    ///
    /// \param i_row row of the element to access.
    /// \param i_col column of the element to access.
    ///
    /// \return element at row \p i_row and column \p i_column.
    inline const ElementT& operator()( size_t i_row, size_t i_column ) const
    {
        return m_elements[ i_row * 4 + i_column ];
    }

    /// Matrix element write-access by row & column.
    ///
    /// \param i_row row of the element to access.
    /// \param i_col column of the element to access.
    ///
    /// \return element at row \p i_row and column \p i_column.
    inline ElementT& operator()( size_t i_row, size_t i_column )
    {
        return m_elements[ i_row * 4 + i_column ];
    }

private:
    /// Container of matrix element memory.
    ElementT m_elements[ M * N ] = {0};
};

LINEAR_ALGEBRA_NS_CLOSE
