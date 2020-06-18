
#include <catch2/catch.hpp>

#include <linear/matrix.h>
#include <linear/transpose.h>

TEST_CASE( "Matrix_Transpose" )
{
    linear::Matrix< 3, 2 > matrix(
        1, 2,
        1, 1,
        2, 2
    );
    CHECK( linear::Transpose( matrix ) == linear::Matrix< 2, 3 >(
        1, 1, 2,
        2, 1, 2
    ) );
}

TEST_CASE( "Matrix_Transpose_constexpr" )
{
    constexpr linear::Matrix< 3, 2 > matrix(
        1, 2,
        1, 1,
        2, 2
    );

    static_assert( linear::Transpose( matrix ) == linear::Matrix< 2, 3 >(
        1, 1, 2,
        2, 1, 2
    ) );
}
