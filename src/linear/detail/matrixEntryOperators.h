#pragma once

/// \file matrixEntryOperators.h
///
/// A collection matrix entry operators, for performing a \em unit of work on an <em>row column indexed</em> entry
/// in a single or set of matrices(s),
///
/// These are generally used to perform the work inside an over-arching traversal pattern.

LINEAR_ALGEBRA_NS_OPEN

/// \class MatrixEntrySet
///
/// Matrix entry value set operator functor.
///
/// \tparam MatrixT the type of matrix.
template < typename MatrixT >
class MatrixEntrySet
{
public:
    /// \param i_value the value to set.
    MatrixEntrySet( typename MatrixT::EntryType i_value )
        : m_value( i_value )
    {
    }

    /// Invoke the operator.
    ///
    /// \param i_rowIndex the row index of the entry.
    /// \param i_columnIndex the row index of the entry.
    /// \param o_matrix the matrix to mutate.
    void operator()( size_t i_rowIndex, size_t i_columnIndex, MatrixT& o_matrix )
    {
        o_matrix( i_rowIndex, i_columnIndex ) = m_value;
    }

private:
    typename MatrixT::EntryType m_value;
};


LINEAR_ALGEBRA_NS_CLOSE
