
#include <catch2/catch.hpp>

#include <linear/matrix.h>
#include <linear/transpose.h>

TEST_CASE( "Matrix_Transpose" )
{
    linear::Matrix< 3, 2 > matrix(
        1.0f, 2.0f,
        1.0f, 1.0f,
        2.0f, 2.0f
    );
    CHECK( linear::Transpose( matrix ) == linear::Matrix< 2, 3 >(
        1.0f, 1.0f, 2.0f,
        2.0f, 1.0f, 2.0f
    ) );
}

TEST_CASE( "Matrix_Transpose_constexpr" )
{
    constexpr linear::Matrix< 3, 2 > matrix(
        1.0f, 2.0f,
        1.0f, 1.0f,
        2.0f, 2.0f
    );

    static_assert( linear::Transpose( matrix ) == linear::Matrix< 2, 3 >(
        1.0f, 1.0f, 2.0f,
        2.0f, 1.0f, 2.0f
    ) );
}
