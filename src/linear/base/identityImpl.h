#pragma once

/// \file identityImpl.h
///
/// Implementation details to produce a compile-time generated identity matrix.

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

template< typename MatrixT, std::size_t Index >
constexpr int _IdentityEntry()
{
    // Matrix must be square.
    static_assert( MatrixT::RowCount() == MatrixT::ColumnCount() );

    // 1's down the main diagonal. 0 otherwise.
    if constexpr ( Index % ( MatrixT::RowCount() + 1 ) == 0 )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

template < typename MatrixT, std::size_t... I >
constexpr MatrixT _IndicesToIdentity( std::index_sequence< I... > )
{
    return MatrixT( _IdentityEntry< MatrixT, I >() ... );
}

template < typename MatrixT, typename Indices = std::make_index_sequence< MatrixT::EntryCount() > >
constexpr MatrixT _GetIdentity()
{
    return _IndicesToIdentity< MatrixT >( Indices{} );
}

LINEAR_ALGEBRA_NS_CLOSE
