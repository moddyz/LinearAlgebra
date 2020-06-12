#pragma once

/// \file matrix.h
///
/// A matrix is rectangular array of numbers, arranged in to rows and columns (M x N).

#include <linearAlgebra/linearAlgebra.h>
#include <linearAlgebra/setIdentity.h>

LINEAR_ALGEBRA_NS_OPEN

/// \class Matrix
///
/// Class representing a compile-time defined M x N matrix.
///
/// Templatizing the number of rows and columns allow the memory of the matrix
/// to be allocated on the stack, instead of the heap.  This is great for
/// applications with well-defined input and output parameters.
///
/// \tparam ValueType value type of the entries.
/// \tparam M number of rows in this matrix.
/// \tparam N number of columns in this matrix.
template < size_t M, size_t N, typename ValueT = float >
class Matrix
{
public:
    /// \typedef ValueType typedef for the value type of the entries.
    typedef ValueT ValueType;

    /// Default constructor, initializing entrys to \em all zeroes.
    Matrix()
    {
    }

    /// Get the row size of this matrix.
    ///
    /// \return the row size.
    static inline constexpr int RowSize()
    {
        return M;
    }

    /// Get the column size of this matrix.
    ///
    /// \return the column size.
    static inline constexpr int ColumnSize()
    {
        return N;
    }

    /// Get the identity element of matrices of dimensions \p M by \p N.
    ///
    /// \return the identity matrix.
    static inline constexpr Matrix< M, N, ValueT > Identity()
    {
        Matrix< M, N, ValueT > matrix;
        SetIdentity( matrix );
        return matrix;
    }

    /// Matrix entry read-access by row & column.
    ///
    /// \param i_row row of the entry to access.
    /// \param i_col column of the entry to access.
    ///
    /// \return entry at row \p i_row and column \p i_column.
    inline const ValueT& operator()( size_t i_row, size_t i_column ) const
    {
        return m_entries[ i_row * 4 + i_column ];
    }

    /// Matrix entry write-access by row & column.
    ///
    /// \param i_row row of the entry to access.
    /// \param i_col column of the entry to access.
    ///
    /// \return entry at row \p i_row and column \p i_column.
    inline ValueT& operator()( size_t i_row, size_t i_column )
    {
        return m_entries[ i_row * 4 + i_column ];
    }

private:
    /// Container of matrix entries memory.
    ValueT m_entries[ M * N ] = {0};
};

LINEAR_ALGEBRA_NS_CLOSE
