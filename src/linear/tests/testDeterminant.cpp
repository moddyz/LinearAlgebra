#include <catch2/catch.hpp>

#include <linear/determinant.h>

TEST_CASE( "Matrix_Determinant" )
{
    CHECK( linear::Determinant( linear::Matrix< 3, 3 >(
            1, 0, 0,
            0, 1, 0,
            0, 0, 1
        )
    ) == 1 );

    CHECK( linear::Determinant( linear::Matrix< 3, 3 >(
            1, 2, 3,
            2, 2, 3,
            3, 3, 3
        )
    ) == 3 );
}
