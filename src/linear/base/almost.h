#pragma once

/// \file base/almost.h

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

/// Function for comparing whether two values \p i_valueA and \p i_valueB are almost equal,
/// within the threshold \p i_epsilon.
///
/// \tparam ValueT the type of value.
///
/// \return whether the input values are within the threshold \p i_epsilon.
template < typename ValueT >
constexpr bool AlmostEqual( const ValueT& i_valueA, const ValueT& i_valueB )
{
    return std::abs( i_valueA - i_valueB ) < 0.0001;
}

LINEAR_ALGEBRA_NS_CLOSE
