#pragma once

/// \file matrix.h
///
/// A matrix is rectangular array of numbers, arranged in to rows and columns (RowSize x N).

#include <linearAlgebra/linearAlgebra.h>

LINEAR_ALGEBRA_NS_OPEN

/// \class Matrix
///
/// Templatized class encoding a M x N matrix.
///
/// \tparam ElementType value type of the elements.
/// \tparam M number of rows in this matrix.
/// \tparam N number of columns in this matrix.
template < size_t M, size_t N, typename ElementT = float >
class Matrix
{
public:
    /// Default constructor, initializing elements to _all_ zeroes.
    Matrix()
    {
    }

    /// Get the row size of this matrix.
    constexpr int RowSize() const
    {
        return M;
    }

    /// Get the column size of this matrix.
    constexpr int ColumnSize() const
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
    /// Storage of matrix memory.
    ElementT m_elements[ M * N ] = {0};
};

LINEAR_ALGEBRA_NS_CLOSE
