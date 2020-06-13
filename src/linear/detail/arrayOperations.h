#pragma once

/// \file arrayOperations.h
///
/// Compile-time recursion for performing an unary or binary operation on <em>every single entry</em> of a
/// set of objects, whom allow for single array indexing.
///
/// For example, to add the corresponding entries of matrices \p A and \p B, and store into matrix \p C:
/// \code{.cpp}
/// linear::Matrix< 5, 5 > A, B, C;
/// linear::ArrayBinaryOperation( ArrayEntryAddition< A::MatrixType >, A, B, C );
/// \endcode

#include <type_traits>

LINEAR_ALGEBRA_NS_OPEN

/// The \em terminating overload of a entry-wise binary operation, between \p i_lhs and \p i_rhs, and writing to
/// \p o_output.
///
/// \tparam ArrayBinaryOperatorT the function prototype of the binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// \param i_operator the binary operator to perform.
/// \param i_lhs the left-hand-side array.
/// \param i_rhs the right-hand-side array.
/// \param o_output the output array.
///
/// The template recursion terminates when \p Index equals \ref ArrayT::EntryCount().
template < typename ArrayBinaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index == ArrayT::EntryCount() >::type* = nullptr >
void ArrayBinaryOperation( ArrayBinaryOperatorT i_operator, const ArrayT& i_lhs, const ArrayT& i_rhs, ArrayT& o_output )
{
    // Nothing to do in this terminating overload.
}

/// The \p operational code path taken to perform an entry-wise binary operation the matrices \p i_lhs and \p i_rhs,
/// storing the result in \p o_output.
///
/// \pre The \em shape of \p i_lhs, \p i_rhs, and \p o_output \em must be the same!
///
/// \tparam ArrayBinaryOperatorT the function prototype of the binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// \param i_operator the binary operator to perform.
/// \param i_lhs the left-hand-side array.
/// \param i_rhs the right-hand-side array.
/// \param o_output the output array.
///
/// This overload code path is taken when \p Index is not equal the \ref ArrayT::EntryCount().
template < typename ArrayBinaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index != ArrayT::EntryCount() >::type* = nullptr >
void ArrayBinaryOperation( ArrayBinaryOperatorT i_operator, const ArrayT& i_lhs, const ArrayT& i_rhs, ArrayT& o_output )
{
    // Execute for one entry of the operation.
    i_operator( Index, i_lhs, i_rhs, o_output );

    // Recursively expand to execute on all other elements...
    ArrayBinaryOperation< ArrayBinaryOperatorT, ArrayT, Index + 1 >( i_operator, i_lhs, i_rhs, o_output );
}

/// The \em terminating overload of a entry-wise equality comparison, between \p i_lhs and \p i_rhs.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// \tparam ArrayT the array type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// The template recursion terminates when \p Index equals \ref ArrayT::EntryCount().
template < typename ArrayT, int Index = 0, typename std::enable_if< Index == ArrayT::EntryCount() >::type* = nullptr >
bool ArrayEquality( const ArrayT& i_lhs, const ArrayT& i_rhs )
{
    // Nothing to do in this terminating overload.
    return true;
}

/// The \em operational overload of a entry-wise equality comparison, between \p i_lhs and \p i_rhs.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// \tparam ArrayT the array type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// This code path is taken when \p Index is not equal the \ref ArrayT::EntryCount().
template < typename ArrayT, int Index = 0, typename std::enable_if< Index != ArrayT::EntryCount() >::type* = nullptr >
bool ArrayEquality( const ArrayT& i_lhs, const ArrayT& i_rhs )
{
    // For N = ArrayT::EntryCount(), this expands to:
    //
    // return ( i_lhs[ 0 ] == i_rhs[ 0 ] ) &&
    //        ( i_lhs[ 0 ] == i_rhs[ 1 ] ) &&
    //        ...
    //        ( i_lhs[ N ] == i_rhs[ N ] );

    return ( i_lhs[ Index ] == i_rhs[ Index ] ) && ArrayEquality< ArrayT, Index + 1 >( i_lhs, i_rhs );
}

LINEAR_ALGEBRA_NS_CLOSE
