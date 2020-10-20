#include <catch2/catch.hpp>

#include <linear/rank.h>

TEST_CASE( "Matrix_MaxRank" )
{
    using MatrixT = linear::Matrix< 3, 4 >;
    CHECK( linear::MaxRank< MatrixT >() == 3 );
}

TEST_CASE( "Matrix_Rank" )
{
    using MatrixT = linear::Matrix< 3, 4 >;
    MatrixT matrix(
        1.0f, 2.0f, 2.0f, 2.0f,
        2.0f, 4.0f, 6.0f, 8.0f,
        3.0f, 6.0f, 8.0f, 10.0f
    );
    CHECK( linear::Rank( matrix ) == 2 );
}
