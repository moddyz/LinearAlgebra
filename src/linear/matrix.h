#pragma once

/// \file matrix.h
///
/// A matrix is rectangular array of numbers, arranged in to rows and columns.

#include <linear/linear.h>

#include <linear/base/almost.h>
#include <linear/base/assert.h>
#include <linear/base/matrixIdentity.h>
#include <linear/base/sequenceOperations.h>
#include <linear/base/typeName.h>

#include <cmath>
#include <cstring>
#include <sstream>

LINEAR_ALGEBRA_NS_OPEN

/// \class Matrix
///
/// Class representing a ROWS x COLS \em dense matrix.
///
/// The row & column count(s) (ROWS, and COLS) are templated so that the required memory allocation
/// of a given matrix is known at compile time, thus can be allocated on the stack.
///
/// ROWS and COLS define the \em shape of the matrix.
///
/// \tparam ROWS number of rows in this matrix.
/// \tparam COLS number of columns in this matrix.
/// \tparam ValueT value type of the entries.
template < size_t ROWS, size_t COLS, typename ValueT = float >
class Matrix final
{
public:
    /// \var ValueType
    ///
    /// Convenience type definition for the value type of the entries.
    using ValueType = ValueT;

    /// \var MatrixType
    ///
    /// Convenience type definition for the current matrix type.
    using MatrixType = Matrix< ROWS, COLS, ValueT >;

    //
    // Constructors.
    //

    /// Default constructor, initializing entries to \em all zeroes.
    constexpr Matrix()
    {
    }

    /// Packed parameter list constructor, initializing entries to \p i_entries.
    ///
    /// \p i_entries should be a row-major indexed sequence of values.
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
        std::memcpy( ( void* ) m_entries, ( const void* ) i_matrix.m_entries, sizeof( MatrixType ) );
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
    }

    /// Copy assignment operator.
    Matrix& operator=( const MatrixType& i_matrix )
    {
        std::memcpy( ( void* ) m_entries, ( const void* ) i_matrix.m_entries, sizeof( MatrixType ) );
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
        return *this;
    }
#endif

    //
    // Shape query.
    //

    /// Get the row size of this matrix.
    ///
    /// \return The row size.
    constexpr static inline int RowCount()
    {
        return ROWS;
    }

    /// Get the column size of this matrix.
    ///
    /// \return The column size.
    constexpr static inline int ColumnCount()
    {
        return COLS;
    }

    /// Get the total number of entries in this matrix, computed as the product
    /// of the row & column count.
    ///
    /// \return The total number of entries in this matrix.
    constexpr static inline int EntryCount()
    {
        return ROWS * COLS;
    }

    //
    // Entry-access operators.
    //

    /// Matrix entry read-access by row & column indices.
    ///
    /// \param i_rowIndex row of the entry to access.
    /// \param i_columnIndex column of the entry to access.
    ///
    /// \return Value entry at row \p i_rowIndex and column \p i_columnIndex.
    constexpr inline const ValueT& operator()( size_t i_rowIndex, size_t i_columnIndex ) const
    {
        LINEAR_ALGEBRA_ASSERT_MSG( ( i_rowIndex * COLS + i_columnIndex ) < ROWS * COLS,
                                   "Requested (%lu, %lu) exceeded bounds (%lu, %lu)\n",
                                   i_rowIndex,
                                   i_columnIndex,
                                   ROWS,
                                   COLS );
        return m_entries[ i_rowIndex * COLS + i_columnIndex ];
    }

    /// Matrix entry write-access by row & column indices.
    ///
    /// \param i_rowIndex row of the entry to access.
    /// \param i_columnIndex column of the entry to access.
    ///
    /// \return Value entry at row \p i_rowIndex and column \p i_columnIndex.
    constexpr inline ValueT& operator()( size_t i_rowIndex, size_t i_columnIndex )
    {
        LINEAR_ALGEBRA_ASSERT_MSG( ( i_rowIndex * COLS + i_columnIndex ) < ROWS * COLS,
                                   "Requested (%lu, %lu) exceeded bounds (%lu, %lu)\n",
                                   i_rowIndex,
                                   i_columnIndex,
                                   ROWS,
                                   COLS );
        return m_entries[ i_rowIndex * COLS + i_columnIndex ];
    }

    /// Matrix entry read-access by single index, with respect to row-major.
    ///
    /// \param i_index the index of the entry to access.
    ///
    /// \return Value entry at entry \p i_index.
    constexpr inline const ValueT& operator[]( size_t i_index ) const
    {
        LINEAR_ALGEBRA_ASSERT_MSG( i_index < ROWS * COLS,
                                   "Requested index %lu exceeds size %lu\n",
                                   i_index,
                                   ROWS * COLS );
        return m_entries[ i_index ];
    }

    /// Matrix entry write-access by single index, with respect to row-major.
    ///
    /// \param i_index the index of the entry to access.
    ///
    /// \return Value entry at entry \p i_index.
    constexpr inline ValueT& operator[]( size_t i_index )
    {
        LINEAR_ALGEBRA_ASSERT_MSG( i_index < ROWS * COLS,
                                   "Requested index %lu exceeds size %lu\n",
                                   i_index,
                                   ROWS * COLS );
        return m_entries[ i_index ];
    }

    //
    // Logical operators.
    //

    /// Equality comparison operator.
    ///
    /// \return true if this matrix and \p i_matrix are \em equal.
    constexpr inline bool operator==( const MatrixType& i_matrix ) const
    {
        return SequenceLogicalBinaryOperation( std::logical_and< bool >(),
                                               AlmostEqual< ValueType >,
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

    //
    // Basic arithmetic operators.
    //

    /// Matrix addition.
    ///
    /// The corresponding entries in the current matrix and \p i_matrix are added and the
    /// resulting matrix returned.
    ///
    /// \pre the current matrix and \p i_matrix must have the same shape.
    constexpr inline MatrixType operator+( const MatrixType& i_matrix ) const
    {
        // TODO How to perform compile-time nan-check?
        // LINEAR_ALGEBRA_ASSERT( !HasNans() );
        return SequenceBinaryOperation( std::plus< ValueType >(), *this, i_matrix );
    }

    /// Matrix subtraction.
    ///
    /// The corresponding entries in the current matrix and \p i_matrix are subtracted and the
    /// resulting matrix returned.
    ///
    /// \pre the current matrix and \p i_matrix must have the same shape.
    constexpr inline MatrixType operator-( const MatrixType& i_matrix ) const
    {
        // TODO How to perform compile-time nan-check?
        // LINEAR_ALGEBRA_ASSERT( !HasNans() );
        return SequenceBinaryOperation( std::minus< ValueType >(), *this, i_matrix );
    }

    /// Matrix addition assignment.
    ///
    /// The entries in \p i_matrix are <em>added to</em> corresponding entries in the current matrix.
    ///
    /// \pre the current matrix and \p i_matrix must have the same shape.
    inline void operator+=( const MatrixType& i_matrix )
    {
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
        MutableSequenceBinaryOperation( std::plus< ValueType >(), *this, i_matrix, *this );
    }

    /// Matrix subtraction assignment.
    ///
    /// The entries in \p i_matrix are <em>subtracted from</em> the corresponding entries in the current matrix.
    ///
    /// \pre the current matrix and \p i_matrix must have the same shape.
    inline void operator-=( const MatrixType& i_matrix )
    {
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
        MutableSequenceBinaryOperation( std::minus< ValueType >(), *this, i_matrix, *this );
    }

    /// Matrix-Scalar multiplication assignment.
    ///
    /// The entries in the current matrix are mutltiplied by a factor of \p i_scalar.
    template < typename ScalarT >
    inline void operator*=( const ScalarT& i_scalar )
    {
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
        MutableSequenceBinaryOperation( std::multiplies< ValueType >(), *this, i_scalar, *this );
    }

    /// Matrix-Scalar division assignment.
    ///
    /// The entries in the current matrix are divided by a factor of \p i_scalar.
    template < typename ScalarT >
    inline void operator/=( const ScalarT& i_scalar )
    {
        LINEAR_ALGEBRA_ASSERT( !HasNans() );
        LINEAR_ALGEBRA_ASSERT( !std::isnan( i_scalar ) );
        LINEAR_ALGEBRA_ASSERT( i_scalar != 0 );
        MutableSequenceBinaryOperation( std::divides< ValueType >(), *this, i_scalar, *this );
    }

    //
    // Linear algebra functionality.
    //

    /// Get the identity matrix.
    ///
    /// \pre \p MatrixType must be a square.
    ///
    /// \return the identity matrix.
    static constexpr inline MatrixType Identity()
    {
        return _GetIdentity< MatrixType >();
    }

    /// Set the current matrix to the identity element.
    ///
    /// \pre The current matrix must be square.
    inline void SetIdentity()
    {
        ( *this ) = _GetIdentity< MatrixType >();
    }

    //
    // Custom functionality.
    //

    /// Check if any of the entries is not a number (NaN).
    ///
    /// \return \p true if any of the entries is not a number.
    constexpr inline bool HasNans() const
    {
        return SequenceLogicalUnaryOperation(
            std::logical_or< bool >(),
            []( ValueType i_entry ) { return std::isnan( i_entry ); },
            /* terminatingValue */ false,
            *this );
    }

    /// Get string representation of this matrix.
    ///
    /// \return String representation of the current matrix.
    inline std::string GetString() const
    {
        std::stringstream ss;
        ss << "Matrix< " << ROWS << ", " << COLS << ", " << std::string( TypeName< ValueT >() ).c_str() << " >(";
        for ( size_t rowIndex = 0; rowIndex < ROWS; ++rowIndex )
        {
            ss << "\n    ";
            for ( size_t columnIndex = 0; columnIndex < COLS; ++columnIndex )
            {
                ss << m_entries[ rowIndex * COLS + columnIndex ];
                if ( columnIndex + 1 < COLS )
                {
                    ss << ", ";
                }
            }

            if ( rowIndex + 1 < ROWS )
            {
                ss << ", ";
            }
        }
        ss << "\n)";
        return ss.str();
    }

private:
    /// Container of matrix entries memory, default initialized to all zeroes.
    ValueT m_entries[ ROWS * COLS ] = {0};
};

/// Operator overload for << to enable writing the string representation of \p i_matrix into an output
/// stream \p o_outputStream.
///
/// \param o_outputStream the output stream to write into.
/// \param i_matrix the source vector value type.
///
/// \return the output stream.
template < size_t ROWS, size_t COLS, typename ValueT >
inline std::ostream& operator<<( std::ostream& o_outputStream, const Matrix< ROWS, COLS, ValueT >& i_matrix )
{
    o_outputStream << i_matrix.GetString();
    return o_outputStream;
}

/// Matrix-Scalar multiplication.
///
/// \param i_matrix the lhs matrix.
/// \param i_scalar the rhs scalar factor.
///
/// \return the computed matrix such that every entry in \p i_matrix is multiplied by a factor of \p i_scalar.
template < size_t ROWS, size_t COLS, typename ValueT >
constexpr inline Matrix< ROWS, COLS, ValueT > operator*( const Matrix< ROWS, COLS, ValueT >& i_matrix,
                                                         const ValueT&                       i_scalar )
{
    return SequenceBinaryOperation( std::multiplies< ValueT >(), i_matrix, i_scalar );
}

/// Scalar-Matrix multiplication.
///
/// \param i_scalar the lhs scalar factor.
/// \param i_matrix the rhs matrix.
///
/// \return the computed matrix such that every entry in \p i_matrix is multiplied by a factor of \p i_scalar.
template < size_t ROWS, size_t COLS, typename ValueT >
constexpr inline Matrix< ROWS, COLS, ValueT > operator*( const ValueT&                       i_scalar,
                                                         const Matrix< ROWS, COLS, ValueT >& i_matrix )
{
    return SequenceBinaryOperation( std::multiplies< ValueT >(), i_matrix, i_scalar );
}

/// Matrix-Scalar division.
///
/// \param i_matrix the lhs matrix.
/// \param i_scalar the rhs scalar factor.
///
/// \return the computed matrix such that every entry in \p i_matrix is divided by a factor of \p i_scalar.
template < size_t ROWS, size_t COLS, typename ValueT >
constexpr inline Matrix< ROWS, COLS, ValueT > operator/( const Matrix< ROWS, COLS, ValueT >& i_matrix,
                                                         const ValueT&                       i_scalar )
{
    LINEAR_ALGEBRA_ASSERT( i_scalar != 0 );
    return SequenceBinaryOperation( std::divides< ValueT >(), i_matrix, i_scalar );
}

LINEAR_ALGEBRA_NS_CLOSE
