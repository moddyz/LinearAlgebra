#include <catch2/catch.hpp>

#include <linear/determinant.h>

TEST_CASE( "Matrix_Determinant" )
{
    CHECK( linear::Determinant( linear::Matrix< 3, 3 >(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f
        )
    ) == 1.0f );

    CHECK( linear::Determinant( linear::Matrix< 3, 3 >(
            1.0f, 2.0f, 3.0f,
            2.0f, 2.0f, 3.0f,
            3.0f, 3.0f, 3.0f
        )
    ) == 3.0f );
}
