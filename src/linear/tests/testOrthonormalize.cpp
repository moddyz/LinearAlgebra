#include <catch2/catch.hpp>

#include <linear/orthonormalize.h>

#include <iostream>

TEST_CASE( "Matrix_Orthonormalize" )
{
    CHECK( linear::Orthonormalize( linear::Matrix< 4, 2 >(
            1, -2,
            1,  0,
            1,  1,
            1,  3
        )
    ) == linear::Matrix< 4, 2 >(
            0.5, -0.693375,
            0.5, -0.138675,
            0.5,  0.138675,
            0.5,  0.693375
        )
    );

    CHECK( linear::Orthonormalize( linear::Matrix< 3, 3 >(
            1, 2, 4,
            0, 0, 5,
            0, 3, 6
        )
    ) == linear::Matrix< 3, 3 >(
            1, 0, 0,
            0, 0, 1,
            0, 1, 0
        )
    );
}
