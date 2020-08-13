#include <catch2/catch.hpp>

#include <linear/row.h>

TEST_CASE( "RowExchange" )
{
    linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    linear::RowExchange( 0, 1, matrix );
    CHECK( matrix == linear::Matrix< 3, 3 >( 0, 1, 0, 1, 0, 0, 0, 0, 1 ) );
}

