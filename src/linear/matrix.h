#pragma once

/// \file matrix.h
///
/// A matrix is rectangular array of numbers, arranged in to rows and columns (M x N).

#include <linear/linear.h>
#include <linear/identity.h>

#include <linear/base/almost.h>
#include <linear/base/assert.h>
#include <linear/base/typeName.h>

#include <linear/detail/arrayOperations.h>

#include <cmath>
#include <cstring>
#include <sstream>

LINEAR_ALGEBRA_NS_OPEN

/// \class Matrix
///
/// Class representing a M x N \em dense matrix.
///
/// The row & column count(s) (M, and N) are templated so that the required memory allocation
/// of a given matrix is known at compile time, thus can be allocated on the stack.
///
/// M and N define the \em shape of the matrix.
///
/// \tparam M number of rows in this matrix.
/// \tparam N number of columns in this matrix.
/// \tparam ValueT value type of the entries.
template < size_t M, size_t N, typename ValueT = float >
class Matrix
{
public:
    /// \typedef EntryType typedef for the value type of the entries.
    using EntryType = ValueT;

    /// \typedef MatrixType typedef for the current matrix type.
    using MatrixType = Matrix< M, N, ValueT >;

    /// Default constructor, initializing entries to \em all zeroes.
    constexpr Matrix()
    {
    }

    /// Initializer list constructor, initializing entries to \p i_entries.
    ///
    /// \p i_entries should be a row-major indexed array of values.
    ///
    /// \pre \p i_entries.size() must equal EntryCount().
    template < typename... Args >
    constexpr Matrix( Args... i_entries )
        : m_entries{i_entries...}
    {
        static_assert( sizeof...( i_entries ) == EntryCount() );
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
    /// \return The row size.
    constexpr static inline int RowCount()
    {
        return M;
    }

    /// Get the column size of this matrix.
    ///
    /// \return The column size.
    constexpr static inline int ColumnCount()
    {
        return N;
    }

    /// Get the total number of entries in this matrix, computed as the product
    /// of the row & column count.
    ///
    /// \return The total number of entries in this matrix.
    constexpr static inline int EntryCount()
    {
        return M * N;
    }

    /// Matrix entry read-access by row & column indices.
    ///
    /// \param i_rowIndex row of the entry to access.
    /// \param i_columnIndex column of the entry to access.
    ///
    /// \return Value entry at row \p i_rowIndex and column \p i_columnIndex.
    constexpr inline const ValueT& operator()( size_t i_rowIndex, size_t i_columnIndex ) const
    {
        return m_entries[ i_rowIndex * N + i_columnIndex ];
    }

    /// Matrix entry write-access by row & column indices.
    ///
    /// \param i_rowIndex row of the entry to access.
    /// \param i_columnIndex column of the entry to access.
    ///
    /// \return Value entry at row \p i_rowIndex and column \p i_columnIndex.
    constexpr inline ValueT& operator()( size_t i_rowIndex, size_t i_columnIndex )
    {
        return m_entries[ i_rowIndex * N + i_columnIndex ];
    }

    /// Matrix entry read-access by single index, with respect to row-major.
    ///
    /// \param i_index the index of the entry to access.
    ///
    /// \return Value entry at entry \p i_index.
    constexpr inline const ValueT& operator[]( size_t i_index ) const
    {
        return m_entries[ i_index ];
    }

    /// Matrix entry write-access by single index, with respect to row-major.
    ///
    /// \param i_index the index of the entry to access.
    ///
    /// \return Value entry at entry \p i_index.
    constexpr inline ValueT& operator[]( size_t i_index )
    {
        return m_entries[ i_index ];
    }

    /// Equality comparison operator.
    ///
    /// \return true if this matrix and \p i_matrix are \em equal.
    constexpr inline bool operator==( const MatrixType& i_matrix ) const
    {
        return ArrayLogicalBinaryOperation( std::logical_and< bool >(),
                                            AlmostEqual< EntryType >,
                                            /* terminatingValue */ true,
                                            *this,
                                            i_matrix );
    }

    /// In-equality comparison operator.
    ///
    /// \return true if this matrix and \p i_matrix are <em>not equal</em>.
    constexpr inline bool operator!=( const MatrixType& i_matrix ) const
    {
        return !( *this == i_matrix );
    }

    /// Matrix addition.
    ///
    /// Each entry (i, j) in the output matrix is the \em sum of the same
    /// entry (i, j) from this matrix and \p i_matrix.
    ///
    /// \pre this matrix and \p i_matrix must have the same shape.
    constexpr inline MatrixType operator+( const MatrixType& i_matrix ) const
    {
        // TODO How to perform compile-time nan-check?
        // LINEAR_ALGEBRA_ASSERT( !HasNans() );
        return ArrayBinaryOperation( std::plus< EntryType >(), *this, i_matrix );
    }

    /// Matrix subtraction.
    ///
    /// Each entry (i, j) in the output matrix is the \em difference of the same
    /// entry (i, j) from this matrix and \p i_matrix.
    ///
    /// \pre this matrix and \p i_matrix must have the same shape.
    constexpr inline MatrixType operator-( const MatrixType& i_matrix ) const
    {
        // TODO How to perform compile-time nan-check?
        // LINEAR_ALGEBRA_ASSERT( !HasNans() );
        return ArrayBinaryOperation( std::minus< EntryType >(), *this, i_matrix );
    }

    /// Get the identity element of matrices of dimensions \p M by \p N.
    ///
    /// \pre Must be a square matrix.
    ///
    /// \return The identity matrix.
    constexpr static inline MatrixType Identity()
    {
        return GetIdentity< MatrixType >();
    }

    /// Check if any of the entries is not a number (NaN).
    ///
    /// \return \p true if any of the entries is not a number.
    constexpr inline bool HasNans() const
    {
        return ArrayLogicalUnaryOperation(
            std::logical_or< bool >(),
            []( EntryType i_entry ) { return std::isnan( i_entry ); },
            /* terminatingValue */ false,
            *this );
    }

    /// Get string representation of this matrix.
    ///
    /// \return String representation of the current matrix.
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
template < size_t M, size_t N, typename ValueT = float >
inline std::ostream& operator<<( std::ostream& o_outputStream, const Matrix< M, N, ValueT >& i_matrix )
{
    o_outputStream << i_matrix.GetString();
    return o_outputStream;
}

LINEAR_ALGEBRA_NS_CLOSE
