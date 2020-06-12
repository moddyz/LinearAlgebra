#pragma once

/// \file matrix.h
///
/// A matrix is rectangular array of numbers, arranged in to rows and columns (M x N).

#include <linearAlgebra/linearAlgebra.h>
#include <linearAlgebra/setIdentity.h>

#include <linearAlgebra/base/almost.h>
#include <linearAlgebra/base/assert.h>
#include <linearAlgebra/base/typeName.h>

#include <cmath>
#include <cstring>
#include <sstream>

LINEAR_ALGEBRA_NS_OPEN

/// \class Matrix
///
/// Class representing a compile-time defined M x N matrix.
///
/// Templatizing the number of rows and columns allow the memory of the matrix
/// to be allocated on the stack, instead of the heap.  This is great for
/// applications with well-defined input and output parameters.
///
/// \tparam EntryType value type of the entries.
/// \tparam M number of rows in this matrix.
/// \tparam N number of columns in this matrix.
template < size_t M, size_t N, typename ValueT = float >
class Matrix
{
public:
    /// \typedef EntryType typedef for the value type of the entries.
    typedef ValueT                 EntryType;
    typedef Matrix< M, N, ValueT > MatrixType;

    /// Default constructor, initializing entries to \em all zeroes.
    Matrix()
    {
    }

#ifdef LINEAR_ALGEBRA_DEBUG
    /// Copy constructor.
    Matrix( const MatrixType& i_matrix )
    {
        std::memcpy( ( void* ) m_entries, ( const void* ) i_matrix.m_entries, sizeof( MatrixType ) * EntryCount() );
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
    }

    /// Copy assignment operator.
    Matrix& operator=( const MatrixType& i_matrix )
    {
        std::memcpy( ( void* ) m_entries, ( const void* ) i_matrix.m_entries, sizeof( MatrixType ) * EntryCount() );
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
        return *this;
    }
#endif

    /// Get the row size of this matrix.
    ///
    /// \return the row size.
    static inline constexpr int RowCount()
    {
        return M;
    }

    /// Get the column size of this matrix.
    ///
    /// \return the column size.
    static inline constexpr int ColumnCount()
    {
        return N;
    }

    /// Get the total number of entries in this matrix, computed as the product
    /// of the row & column count.
    ///
    /// \return the total number of entries in this matrix.
    static inline constexpr int EntryCount()
    {
        return M * N;
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
    /// \param i_rowIndex row of the entry to access.
    /// \param i_columnIndex column of the entry to access.
    ///
    /// \return entry at row \p i_rowIndex and column \p i_columnIndex.
    inline const ValueT& operator()( size_t i_rowIndex, size_t i_columnIndex ) const
    {
        return m_entries[ i_rowIndex * N + i_columnIndex ];
    }

    /// Matrix entry write-access by row & column.
    ///
    /// \param i_rowIndex row of the entry to access.
    /// \param i_columnIndex column of the entry to access.
    ///
    /// \return entry at row \p i_rowIndex and column \p i_columnIndex.
    inline ValueT& operator()( size_t i_rowIndex, size_t i_columnIndex )
    {
        return m_entries[ i_rowIndex * N + i_columnIndex ];
    }

    /// Check if any of the entries is not a number (NaN).
    ///
    /// \return true if any of the entries is not a number.
    inline bool HasNans() const
    {
        for ( size_t entryIndex = 0; entryIndex < ( M * N ); ++entryIndex )
        {
            if ( std::isnan( m_entries[ entryIndex ] ) )
            {
                return true;
            }
        }

        return false;
    }

    /// Get string representation of this matrix.
    ///
    /// \return string representation.
    inline std::string GetString() const
    {
        std::stringstream ss;
        ss << "Matrix< " << M << ", " << N << ", " << std::string( TypeName< ValueT >() ).c_str() << " >(";
        for ( size_t rowIndex = 0; rowIndex < M; ++rowIndex )
        {
            ss << "\n    ";
            for ( size_t columnIndex = 0; columnIndex < N; ++columnIndex )
            {
                ss << m_entries[ rowIndex * N + columnIndex ];
                if ( columnIndex + 1 < N )
                {
                    ss << ", ";
                }
            }
        }
        return ss.str();
    }

private:
    /// Container of matrix entries memory, default initialized to all zeroes.
    ValueT m_entries[ M * N ] = {0};
};

/// Operator overload for << to enable writing the string representation of \p i_matrix into an output
/// stream \p o_outputStream.
///
/// \param o_outputStream the output stream to write into.
/// \param i_matrix the source vector value type.
///
/// \return the output stream.
template < typename MatrixT >
inline std::ostream& operator<<( std::ostream& o_outputStream, const MatrixT& i_matrix )
{
    o_outputStream << i_matrix.GetString();
    return o_outputStream;
}

LINEAR_ALGEBRA_NS_CLOSE
