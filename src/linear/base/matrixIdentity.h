#pragma once

/// \file identityImpl.h
///
/// Implementation details to produce a compile-time generated identity matrix.
///
/// The entry point is \ref linear::_GetIdentity, so read from bottom up.

#include <linear/linear.h>

LINEAR_ALGEBRA_NS_OPEN

/// Converts a sequence index into the respective identity matrix value.
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

/// Expand each index sequence element \p EntryIndex, to form packed parameters to construct \p MatrixT.
template < typename MatrixT, std::size_t... EntryIndex >
constexpr MatrixT _GetIdentityIndexExpansion( std::index_sequence< EntryIndex... > )
{
    return MatrixT( _IdentityEntry< MatrixT, EntryIndex >() ... );
}

/// Generate an index_sequence of size \ref Matrix::EntryCount().
template < typename MatrixT, typename EntryIndices = std::make_index_sequence< MatrixT::EntryCount() > >
constexpr MatrixT _GetIdentity()
{
    return _GetIdentityIndexExpansion< MatrixT >( EntryIndices{} );
}

LINEAR_ALGEBRA_NS_CLOSE
