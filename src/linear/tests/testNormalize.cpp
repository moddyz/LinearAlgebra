#include <catch2/catch.hpp>

#include <linear/normalize.h>

#include <iostream>

TEST_CASE( "Matrix_Normalize" )
{
    CHECK( linear::Normalize( linear::Matrix< 3, 1 >(
            1.0f,
            0.0f,
            0.0f
        )
    )  == linear::Matrix< 3, 1 >(
            1.0f,
            0.0f,
            0.0f
        )
    );

    CHECK( linear::Normalize( linear::Matrix< 3, 1 >(
            3.0f,
            4.0f,
            5.0f
        )
    )  == linear::Matrix< 3, 1 >(
            0.424264f,
            0.565685f,
            0.707107f
        )
    );
}
