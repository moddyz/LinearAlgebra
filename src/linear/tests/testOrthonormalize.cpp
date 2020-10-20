#include <catch2/catch.hpp>

#include <linear/orthonormalize.h>

#include <iostream>

TEST_CASE( "Matrix_Orthonormalize" )
{
    CHECK( linear::Orthonormalize( linear::Matrix< 4, 2 >(
            1.0f, -2.0f,
            1.0f,  0.0f,
            1.0f,  1.0f,
            1.0f,  3.0f
        )
    ) == linear::Matrix< 4, 2 >(
            0.5f, -0.693375f,
            0.5f, -0.138675f,
            0.5f,  0.138675f,
            0.5f,  0.693375f
        )
    );

    CHECK( linear::Orthonormalize( linear::Matrix< 3, 3 >(
            1.0f, 2.0f, 4.0f,
            0.0f, 0.0f, 5.0f,
            0.0f, 3.0f, 6.0f
        )
    ) == linear::Matrix< 3, 3 >(
            1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            0.0f, 1.0f, 0.0f
        )
    );
}
