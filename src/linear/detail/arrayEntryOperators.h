#pragma once

/// \file arrayEntryOperators.h
///
/// A collection array entry operators, for performing a \em unit of work on an <em>single array indexed</em>
/// entry on an array or set of array(s),
///
/// These are generally used to perform the work inside an over-arching traversal pattern.

LINEAR_ALGEBRA_NS_OPEN

/// Array entry addition operator.
///
/// \param i_index the index of the entry to access as an array.
/// \param i_lhs the left-hand-side matrix.
/// \param i_rhs the right-hand-side matrix.
/// \param o_output the matrix to store the sum of the corresponding entries.
///
/// \tparam ArrayT the type of array-like object.
template < typename ArrayT >
void ArrayEntryAddition( size_t i_index, const ArrayT& i_lhs, const ArrayT& i_rhs, ArrayT& o_output )
{
    o_output[ i_index ] = i_lhs[ i_index ] + i_rhs[ i_index ];
}

LINEAR_ALGEBRA_NS_CLOSE
