#pragma once

/// \file sequenceOperations.h
///
/// Compile-time recursion for performing an unary or binary operation on <em>every single entry</em> of a
/// set of Sequence objects. Template function recursion and index sequence techniques are both used in the.
///
/// A Sequence object is defined to support indexing via operator[].
///
/// For example, to add the corresponding entries of matrices \p A and \p B, and store into matrix \p C:
/// \code{.cpp}
/// linear::Matrix< 5, 5 > A, B;
/// linear::Matrix< 5, 5 > C = linear::SequenceBinaryOperation( std::plus< float >(), A, B );
/// \endcode
///
/// Although matrices are traditionally indexed by two components (row, column), the Matrix::operator[] has been
/// overloaded to perform a operations on every single entry

#include <linear/linear.h>

#include <type_traits>

LINEAR_NS_OPEN

/// This is a helper function for the sequence * sequence variation of  \ref SequenceBinaryOperation, which expands the
/// index sequence into a series of operations.
template < typename BinaryOperatorT, typename SequenceT, std::size_t... Index >
constexpr SequenceT SequenceIndexedBinaryOperation( BinaryOperatorT  i_binaryOperator,
                                                    const SequenceT& i_lhs,
                                                    const SequenceT& i_rhs,
                                                    std::index_sequence< Index... > )
{
    return SequenceT( i_binaryOperator( i_lhs[ Index ], i_rhs[ Index ] )... );
}

/// Perform a binary operation on the corresponding entries of two sequences, and return the computed sequence.
///
/// \tparam BinaryOperatorT the function prototype of the logical binary operation to perform.
/// \tparam SequenceT the sequence type.
/// \tparam Indices the index sequence with respect to the number of sequence entries.
///
/// \param i_binaryOperator the binary operator function object.
/// \param i_lhs lhs sequence to operate on.
/// \param i_rhs rhs sequence to operate on.
///
/// \return the computed sequence.
template < typename BinaryOperatorT,
           typename SequenceT,
           typename Indices = std::make_index_sequence< SequenceT::EntryCount() > >
constexpr SequenceT
SequenceBinaryOperation( BinaryOperatorT i_binaryOperator, const SequenceT& i_lhs, const SequenceT& i_rhs )
{
    return SequenceIndexedBinaryOperation( i_binaryOperator, i_lhs, i_rhs, Indices{} );
}

/// \overload
///
/// This is a helper function for the sequence * scalar variation of \ref SequenceBinaryOperation, which expands the
/// index sequence into a series of operations.
template < typename BinaryOperatorT, typename SequenceT, std::size_t... Index >
constexpr SequenceT SequenceIndexedBinaryOperation( BinaryOperatorT                      i_binaryOperator,
                                                    const SequenceT&                     i_lhs,
                                                    const typename SequenceT::ValueType& i_rhs,
                                                    std::index_sequence< Index... > )
{
    return SequenceT( i_binaryOperator( i_lhs[ Index ], i_rhs )... );
}

/// \overload
///
/// This is an overload of \ref SequenceBinaryOperation which multiplies each sequence entry with a \em scalar
/// right-hand side.
template < typename BinaryOperatorT,
           typename SequenceT,
           typename Indices = std::make_index_sequence< SequenceT::EntryCount() > >
constexpr SequenceT SequenceBinaryOperation( BinaryOperatorT                      i_binaryOperator,
                                             const SequenceT&                     i_lhs,
                                             const typename SequenceT::ValueType& i_rhs )
{
    return SequenceIndexedBinaryOperation( i_binaryOperator, i_lhs, i_rhs, Indices{} );
}

/// The \em terminating overload of the sequence * sequence \ref MutableSequenceBinaryOperation.
template < typename BinaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index == SequenceT::EntryCount() >::type* = nullptr >
void MutableSequenceBinaryOperation( BinaryOperatorT  i_binaryOperator,
                                     const SequenceT& i_lhs,
                                     const SequenceT& i_rhs,
                                     SequenceT&       o_output )
{
    // Nothing to do in this terminating overload.
}

/// The \em operational overload of a binary operation performed on two sequences.
///
/// This is a variation of \ref SequenceBinaryOperation which cannot be used in a constexpr, because
/// it modifies the memory of \p o_output.  For example, this is used to implement the arithmetic
/// assignment operators of the \ref Matrix class.
///
/// \pre The \em shape of \p i_lhs, \p i_rhs, and \p o_output \em must be the same!
///
/// This overload code path is taken when \p Index is not equal the sequence count.
///
/// \tparam BinaryOperatorT the function prototype of the binary operation to perform.
/// \tparam SequenceT the sequence type.
/// \tparam Index the index of the entry to make a comparison for.
///
/// \param i_binaryOperator the binary operator to perform.
/// \param i_lhs the left-hand-side sequence.
/// \param i_rhs the right-hand-side sequence.
/// \param o_output the output sequence.
template < typename BinaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index != SequenceT::EntryCount() >::type* = nullptr >
void MutableSequenceBinaryOperation( BinaryOperatorT  i_binaryOperator,
                                     const SequenceT& i_lhs,
                                     const SequenceT& i_rhs,
                                     SequenceT&       o_output )
{
    // Execute for one entry of the operation.
    o_output[ Index ] = i_binaryOperator( i_lhs[ Index ], i_rhs[ Index ] );

    // Recursively expand to execute on all other elements...
    MutableSequenceBinaryOperation< BinaryOperatorT, SequenceT, Index + 1 >( i_binaryOperator, i_lhs, i_rhs, o_output );
}

/// \overload
///
/// The \em terminating overload of the sequence * scalar variant of \ref MutableSequenceBinaryOperation.
template < typename BinaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index == SequenceT::EntryCount() >::type* = nullptr >
void MutableSequenceBinaryOperation( BinaryOperatorT                      i_binaryOperator,
                                     const SequenceT&                     i_lhs,
                                     const typename SequenceT::ValueType& i_rhs,
                                     SequenceT&                           o_output )
{
    // Nothing to do in this terminating overload.
}

/// \overload
///
/// This is an overload of \ref MutableSequenceBinaryOperation which performs binary operation on a sequence \p i_lhs,
/// and a scalar \p i_scalar value.
template < typename BinaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index != SequenceT::EntryCount() >::type* = nullptr >
void MutableSequenceBinaryOperation( BinaryOperatorT                      i_binaryOperator,
                                     const SequenceT&                     i_lhs,
                                     const typename SequenceT::ValueType& i_rhs,
                                     SequenceT&                           o_output )
{
    // Execute for one entry of the operation.
    o_output[ Index ] = i_binaryOperator( i_lhs[ Index ], i_rhs );

    // Recursively expand to execute on all other elements...
    MutableSequenceBinaryOperation< BinaryOperatorT, SequenceT, Index + 1 >( i_binaryOperator, i_lhs, i_rhs, o_output );
}

/// The \em terminating overload of \ref SequenceLogicalBinaryOperation.
template < typename LogicalOperatorT,
           typename BinaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index == SequenceT::EntryCount() >::type* = nullptr >
constexpr bool SequenceLogicalBinaryOperation( LogicalOperatorT i_logicalOperator,
                                               BinaryOperatorT  i_binaryOperator,
                                               bool             i_terminatingValue,
                                               const SequenceT& i_lhs,
                                               const SequenceT& i_rhs )
{
    // Nothing to do in this terminating overload.
    return i_terminatingValue;
}

/// The \em operational overload of a sequence-based logical binary operation, between \p i_lhs and \p i_rhs.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// This code path is taken when \p Index is not equal the SequenceT::EntryCount().
///
/// \tparam LogicalOperatorT the function prototype of the logical operation to perform.
/// \tparam BinaryOperatorT the function prototype binary operation to perform.
/// \tparam SequenceT the sequence type.
/// \tparam Index the index of the sequence entry.
///
/// \param i_logicalOperator the logical operator function object.
/// \param i_binaryOperator the binary operator function object.
/// \param i_terminatingValue the value to return in the terminating overload.
/// \param i_lhs lhs sequence to operate on.
/// \param i_rhs rhs sequence to operate on.
///
/// \return the combined logical result.
template < typename LogicalOperatorT,
           typename BinaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index != SequenceT::EntryCount() >::type* = nullptr >
constexpr bool SequenceLogicalBinaryOperation( LogicalOperatorT i_logicalOperator,
                                               BinaryOperatorT  i_binaryOperator,
                                               bool             i_terminatingValue,
                                               const SequenceT& i_lhs,
                                               const SequenceT& i_rhs )
{
    return i_logicalOperator(
        i_binaryOperator( i_lhs[ Index ], i_rhs[ Index ] ),
        SequenceLogicalBinaryOperation< LogicalOperatorT, BinaryOperatorT, SequenceT, Index + 1 >( i_logicalOperator,
                                                                                                   i_binaryOperator,
                                                                                                   i_terminatingValue,
                                                                                                   i_lhs,
                                                                                                   i_rhs ) );
}

/// The \em terminating overload of \ref SequenceLogicalUnaryOperation.
template < typename LogicalOperatorT,
           typename UnaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index == SequenceT::EntryCount() >::type* = nullptr >
constexpr bool SequenceLogicalUnaryOperation( LogicalOperatorT i_logicalOperator,
                                              UnaryOperatorT   i_unaryOperator,
                                              bool             i_terminatingValue,
                                              const SequenceT& i_sequence )
{
    // Nothing to do in this terminating overload.
    return i_terminatingValue;
}

/// The \em operational overload of a logical combination of unary operations across \p i_sequence.
///
/// \pre The \em shape of \p i_lhs and \p i_rhs \em must be the same!
///
/// This code path is taken when \p Index is not equal the SequenceT::EntryCount().
///
/// \tparam UnaryOperatorT the function prototype of the logical binary operation to perform.
/// \tparam SequenceT the sequence type.
/// \tparam Index the index of the sequence entry.
///
/// \param i_logicalOperator the logical operator function object.
/// \param i_unaryOperator the unary operator function object.
/// \param i_terminatingValue the value to return in the terminating overload.
/// \param i_sequence the sequence to operate on.
///
/// \return the combined logical result.
template < typename LogicalOperatorT,
           typename UnaryOperatorT,
           typename SequenceT,
           int Index                                                          = 0,
           typename std::enable_if< Index != SequenceT::EntryCount() >::type* = nullptr >
constexpr bool SequenceLogicalUnaryOperation( LogicalOperatorT i_logicalOperator,
                                              UnaryOperatorT   i_unaryOperator,
                                              bool             i_terminatingValue,
                                              const SequenceT& i_sequence )
{
    return i_logicalOperator(
        i_unaryOperator( i_sequence[ Index ] ),
        SequenceLogicalUnaryOperation< LogicalOperatorT, UnaryOperatorT, SequenceT, Index + 1 >( i_logicalOperator,
                                                                                                 i_unaryOperator,
                                                                                                 i_terminatingValue,
                                                                                                 i_sequence ) );
}

LINEAR_NS_CLOSE
