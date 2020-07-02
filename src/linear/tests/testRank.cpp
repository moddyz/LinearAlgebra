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
        1, 2, 2, 2,
        2, 4, 6, 8,
        3, 6, 8, 10
    );
    CHECK( linear::Rank( matrix ) == 2 );
}
