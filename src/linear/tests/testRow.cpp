#include <catch2/catch.hpp>

#include <linear/row.h>

TEST_CASE( "GetRow" )
{
    linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    linear::Matrix< 1, 3 > row    = linear::GetRow( matrix, 2 );
    CHECK( row == linear::Matrix< 1, 3 >( 0, 0, 1 ) );
}

TEST_CASE( "GetRow_constexpr" )
{
    constexpr linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    constexpr linear::Matrix< 1, 3 > row    = linear::GetRow( matrix, 2 );
    static_assert( row == linear::Matrix< 1, 3 >( 0, 0, 1 ) );
}

TEST_CASE( "RowExchange" )
{
    linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    linear::RowExchange( 0, 1, matrix );
    CHECK( matrix == linear::Matrix< 3, 3 >( 0, 1, 0, 1, 0, 0, 0, 0, 1 ) );
}

