#pragma once

/// \file entryWise.h
///
/// Compile-time recursion for performing an unary operation on <em> each entry </em> of a Matrix, or a
/// binary operation on <em> corresponding entries</em> of two matrices.
///
/// For example, to add the corresponding entries of matrices A and B, and store into C:
///
/// \code{.cpp}
/// linear::Matrix< 5, 5 > A, B, C;
/// linear::EntryWiseBinaryOperation< decltype(A), linear::
/// \endcode

#include <type_traits>

LINEAR_ALGEBRA_NS_OPEN

/// The \em terminating overload of a entry-wise binary operation, between \p i_lhs and \p i_rhs, and writing to
/// \p o_output.
///
/// \tparam BinaryOperatorT the function prototype of the binary operation to perform.
/// \tparam MartixT the matrix type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// \param i_operator the binary operator to perform.
/// \param i_lhs the left-hand-side matrix.
/// \param i_rhs the right-hand-side matrix.
/// \param o_output the output matrix.
///
/// The template recursion terminates when \p Index equals \ref Matrix::EntryCount().
template < typename BinaryOperatorT,
           typename MatrixT,
           int Index                                                        = 0,
           typename std::enable_if< Index == MatrixT::EntryCount() >::type* = nullptr >
void EntryWiseBinaryOperation( BinaryOperatorT i_operator,
                               const MatrixT&  i_lhs,
                               const MatrixT&  i_rhs,
                               MatrixT&        o_output )
{
    // Nothing to do in this terminating overload.
}

/// The \p operational code path taken to perform an entry-wise binary operation the matrices \p i_lhs and \p i_rhs,
/// storing the result in \p o_output.
///
/// \pre The \em shape of \p i_lhs, \p i_rhs, and \p o_output \em must be the same!
///
/// \tparam BinaryOperatorT the function prototype of the binary operation to perform.
/// \tparam MartixT the matrix type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// \param i_operator the binary operator to perform.
/// \param i_lhs the left-hand-side matrix.
/// \param i_rhs the right-hand-side matrix.
/// \param o_output the output matrix.
///
/// This overload code path is taken when \p Index is not equal the \ref Matrix::EntryCount().
template < typename BinaryOperatorT,
           typename MatrixT,
           int Index                                                        = 0,
           typename std::enable_if< Index != MatrixT::EntryCount() >::type* = nullptr >
void EntryWiseBinaryOperation( BinaryOperatorT i_operator,
                               const MatrixT&  i_lhs,
                               const MatrixT&  i_rhs,
                               MatrixT&        o_output )
{
    // Execute for one entry of the operation.
    i_operator( Index, i_lhs, i_rhs, o_output );

    // Recursively expand to execute on all other elements...
    EntryWiseBinaryOperation< BinaryOperatorT, MatrixT, Index + 1 >( i_operator, i_lhs, i_rhs, o_output );
}

/// Entry-wise addition operator.
///
/// \param i_index the index of the matrix entry to add.
/// \param i_lhs the left-hand-side matrix.
/// \param i_rhs the right-hand-side matrix.
/// \param o_output the matrix to store the sum of the corresponding entries.
///
/// \tparam MatrixT the type of matrix.
template < typename MatrixT >
void EntryWiseAdditionOperator( size_t i_index, const MatrixT& i_lhs, const MatrixT& i_rhs, MatrixT& o_output )
{
    o_output[ i_index ] = i_lhs[ i_index ] + i_rhs[ i_index ];
}

/// The \em terminating overload of a entry-wise equality comparison, between \p i_lhs and \p i_rhs.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// \tparam MartixT the matrix type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// The template recursion terminates when \p Index equals \ref Matrix::EntryCount().
template < typename MatrixT, int Index = 0, typename std::enable_if< Index == MatrixT::EntryCount() >::type* = nullptr >
bool EntryWiseEquality( const MatrixT& i_lhs, const MatrixT& i_rhs )
{
    // Nothing to do in this terminating overload.
    return true;
}

/// The \em operational overload of a entry-wise equality comparison, between \p i_lhs and \p i_rhs.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// \tparam MartixT the matrix type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// This code path is taken when \p Index is not equal the \ref Matrix::EntryCount().
template < typename MatrixT, int Index = 0, typename std::enable_if< Index != MatrixT::EntryCount() >::type* = nullptr >
bool EntryWiseEquality( const MatrixT& i_lhs, const MatrixT& i_rhs )
{
    // For N = MatrixT::EntryCount(), this expands to:
    //
    // return ( i_lhs[ 0 ] == i_rhs[ 0 ] ) &&
    //        ( i_lhs[ 0 ] == i_rhs[ 1 ] ) &&
    //        ...
    //        ( i_lhs[ N ] == i_rhs[ N ] );

    return ( i_lhs[ Index ] == i_rhs[ Index ] ) && EntryWiseEquality< MatrixT, Index + 1 >( i_lhs, i_rhs );
}

LINEAR_ALGEBRA_NS_CLOSE
