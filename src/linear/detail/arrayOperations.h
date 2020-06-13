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

/// Perform a binary operator on the corresponding array entries, and return the computed array.
///
/// \tparam BinaryOperatorT the function prototype of the logical binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Index an index in the sequence.
///
/// \param i_binaryOperator the binary operator function object.
/// \param i_lhs lhs array to operate on.
/// \param i_rhs rhs array to operate on.
///
/// \return the computed array.
template < typename BinaryOperatorT, typename ArrayT, std::size_t... Index >
constexpr ArrayT ArrayIndexSequenceBinaryOperation( BinaryOperatorT i_binaryOperator,
                                                    const ArrayT&   i_lhs,
                                                    const ArrayT&   i_rhs,
                                                    std::index_sequence< Index... > )
{
    return ArrayT( i_binaryOperator( i_lhs[ Index ], i_rhs[ Index ] )... );
}

/// Perform a binary operator on the corresponding array entries, and return the computed array.
///
/// \tparam BinaryOperatorT the function prototype of the logical binary operation to perform.
/// \tparam ArrayT the array type.
/// \tparam Indices the index sequence with respect to the number of array entries.
///
/// \param i_binaryOperator the binary operator function object.
/// \param i_lhs lhs array to operate on.
/// \param i_rhs rhs array to operate on.
///
/// \return the computed array.
template < typename BinaryOperatorT,
           typename ArrayT,
           typename Indices = std::make_index_sequence< ArrayT::EntryCount() > >
constexpr ArrayT ArrayBinaryOperation( BinaryOperatorT i_binaryOperator, const ArrayT& i_lhs, const ArrayT& i_rhs )
{
    return ArrayIndexSequenceBinaryOperation( i_binaryOperator, i_lhs, i_rhs, Indices{} );
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
/// \param i_logicalOperator the logical operator function object.
/// \param i_binaryOperator the binary operator function object.
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

/// \overload
///
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
/// \param i_logicalOperator the logical operator function object.
/// \param i_binaryOperator the binary operator function object.
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
/// \param i_logicalOperator the logical operator function object.
/// \param i_unaryOperator the unary operator function object.
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
/// \param i_logicalOperator the logical operator function object.
/// \param i_unaryOperator the unary operator function object.
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
