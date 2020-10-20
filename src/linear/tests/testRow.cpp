#include <catch2/catch.hpp>

#include <linear/row.h>

TEST_CASE( "RowExchange" )
{
    linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    linear::RowExchange( 0, 1, matrix );
    CHECK( matrix == linear::Matrix< 3, 3 >( 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f ) );
}

