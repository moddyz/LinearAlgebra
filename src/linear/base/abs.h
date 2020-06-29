#pragma once

/// \file base/abs.h

#include <linear/linear.h>

LINEAR_NS_OPEN

/// Compile-time enabled absolute value function.
///
/// \tparam ValueT the value type.
///
/// \param i_value the value to take the absolute value of.
///
/// \return the absolute value.
template< typename ValueT >
constexpr ValueT Abs( const ValueT& i_value )
{
    return i_value >= 0 ? i_value : -i_value;
}

LINEAR_NS_CLOSE
