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

#include <linear/linear.h>

#include <type_traits>

LINEAR_ALGEBRA_NS_OPEN

/// The \em terminating overload of a binary operation performed on arrays.
///
/// \pre The \em shape of \p i_lhs, \p i_rhs, and \p o_output \em must be the same!
///
/// \tparam BinaryOperatorT the function prototype of the binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// \param i_binaryOperator the binary operator to perform.
/// \param i_lhs the left-hand-side array.
/// \param i_rhs the right-hand-side array.
/// \param o_output the output array.
///
/// The template recursion terminates when \p Index equals \ref ArrayT::EntryCount().
template < typename BinaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index == ArrayT::EntryCount() >::type* = nullptr >
void ArrayBinaryOperation( BinaryOperatorT i_binaryOperator,
                           const ArrayT&   i_lhs,
                           const ArrayT&   i_rhs,
                           ArrayT&         o_output )
{
    // Nothing to do in this terminating overload.
}

/// The \em operational overload of a binary operation performed on arrays.
///
/// \pre The \em shape of \p i_lhs, \p i_rhs, and \p o_output \em must be the same!
///
/// \tparam BinaryOperatorT the function prototype of the binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// \param i_binaryOperator the binary operator to perform.
/// \param i_lhs the left-hand-side array.
/// \param i_rhs the right-hand-side array.
/// \param o_output the output array.
///
/// This overload code path is taken when \p Index is not equal the \ref ArrayT::EntryCount().
template < typename BinaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index != ArrayT::EntryCount() >::type* = nullptr >
void ArrayBinaryOperation( BinaryOperatorT i_binaryOperator,
                           const ArrayT&   i_lhs,
                           const ArrayT&   i_rhs,
                           ArrayT&         o_output )
{
    // Execute for one entry of the operation.
    o_output[ Index ] = i_binaryOperator( i_lhs[ Index ], i_rhs[ Index ] );

    // Recursively expand to execute on all other elements...
    ArrayBinaryOperation< BinaryOperatorT, ArrayT, Index + 1 >( i_binaryOperator, i_lhs, i_rhs, o_output );
}

/// The \em terminating overload of a array-based logical binary operation, between \p i_lhs and \p i_rhs.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// \tparam LogicalOperatorT the function prototype of the logical operation to perform.
/// \tparam BinaryOperatorT the function prototype of the logical binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the array entry.
///
/// \param i_logicalOperator function object of the logical operator.
/// \param i_binaryOperator function object of the binary operator.
/// \param i_terminatingValue the value to return in the terminating overload.
/// \param i_lhs lhs array to operate on.
/// \param i_rhs rhs array to operate on.
///
/// \return the combined logical result.
template < typename LogicalOperatorT,
           typename BinaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index == ArrayT::EntryCount() >::type* = nullptr >
constexpr bool ArrayLogicalBinaryOperation( LogicalOperatorT i_logicalOperator,
                                            BinaryOperatorT  i_binaryOperator,
                                            bool             i_terminatingValue,
                                            const ArrayT&    i_lhs,
                                            const ArrayT&    i_rhs )
{
    // Nothing to do in this terminating overload.
    return i_terminatingValue;
}

/// The \em operational overload of a array-based logical binary operation, between \p i_lhs and \p i_rhs.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// This code path is taken when \p Index is not equal the \ref ArrayT::EntryCount().
///
/// \tparam LogicalOperatorT the function prototype of the logical operation to perform.
/// \tparam BinaryOperatorT the function prototype binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the array entry.
///
/// \param i_logicalOperator function object of the logical operator.
/// \param i_binaryOperator function object of the binary operator.
/// \param i_terminatingValue the value to return in the terminating overload.
/// \param i_lhs lhs array to operate on.
/// \param i_rhs rhs array to operate on.
///
/// \return the combined logical result.
template < typename LogicalOperatorT,
           typename BinaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index != ArrayT::EntryCount() >::type* = nullptr >
constexpr bool ArrayLogicalBinaryOperation( LogicalOperatorT i_logicalOperator,
                                            BinaryOperatorT  i_binaryOperator,
                                            bool             i_terminatingValue,
                                            const ArrayT&    i_lhs,
                                            const ArrayT&    i_rhs )
{
    return i_logicalOperator(
        i_binaryOperator( i_lhs[ Index ], i_rhs[ Index ] ),
        ArrayLogicalBinaryOperation< LogicalOperatorT, BinaryOperatorT, ArrayT, Index + 1 >( i_logicalOperator,
                                                                                             i_binaryOperator,
                                                                                             i_terminatingValue,
                                                                                             i_lhs,
                                                                                             i_rhs ) );
}

/// The \em terminating overload of a logical combination of unary operations across \p i_array.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// \tparam UnaryOperatorT the function prototype of the logical uniary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the array entry.
///
/// \param i_logicalOperator function object of the logical operator.
/// \param i_unaryOperator function object of the unary operator.
/// \param i_terminatingValue the value to return in the terminating overload.
/// \param i_array the array to operate on.
///
/// \return the combined logical result.
template < typename LogicalOperatorT,
           typename UnaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index == ArrayT::EntryCount() >::type* = nullptr >
constexpr bool ArrayLogicalUnaryOperation( LogicalOperatorT i_logicalOperator,
                                           UnaryOperatorT   i_unaryOperator,
                                           bool             i_terminatingValue,
                                           const ArrayT&    i_array )
{
    // Nothing to do in this terminating overload.
    return i_terminatingValue;
}

/// The \em operational overload of a logical combination of unary operations across \p i_array.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// This code path is taken when \p Index is not equal the \ref ArrayT::EntryCount().
///
/// \tparam UnaryOperatorT the function prototype of the logical binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index the index of the array entry.
///
/// \param i_logicalOperator function object of the logical operator.
/// \param i_unaryOperator function object of the unary operator.
/// \param i_terminatingValue the value to return in the terminating overload.
/// \param i_array the array to operate on.
///
/// \return the combined logical result.
template < typename LogicalOperatorT,
           typename UnaryOperatorT,
           typename ArrayT,
           int Index                                                       = 0,
           typename std::enable_if< Index != ArrayT::EntryCount() >::type* = nullptr >
constexpr bool ArrayLogicalUnaryOperation( LogicalOperatorT i_logicalOperator,
                                           UnaryOperatorT   i_unaryOperator,
                                           bool             i_terminatingValue,
                                           const ArrayT&    i_array )
{
    return i_logicalOperator(
        i_unaryOperator( i_array[ Index ] ),
        ArrayLogicalUnaryOperation< LogicalOperatorT, UnaryOperatorT, ArrayT, Index + 1 >( i_logicalOperator,
                                                                                           i_unaryOperator,
                                                                                           i_terminatingValue,
                                                                                           i_array ) );
}

LINEAR_ALGEBRA_NS_CLOSE
