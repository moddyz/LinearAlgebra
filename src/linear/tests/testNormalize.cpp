#include <catch2/catch.hpp>

#include <linear/normalize.h>

#include <iostream>

TEST_CASE( "Matrix_Normalize" )
{
    CHECK( linear::Normalize( linear::Matrix< 3, 1 >(
            1,
            0,
            0
        )
    )  == linear::Matrix< 3, 1 >(
            1,
            0,
            0
        )
    );

    CHECK( linear::Normalize( linear::Matrix< 3, 1 >(
            3,
            4,
            5
        )
    )  == linear::Matrix< 3, 1 >(
            0.424264,
            0.565685,
            0.707107
        )
    );
}
