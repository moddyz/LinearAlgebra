#include <catch2/catch.hpp>

#include <linear/projection.h>

TEST_CASE( "Projection" )
{
    linear::Matrix< 3, 1 > vector(
        2,
        3,
        4
    );
    linear::Matrix< 3, 2 > subspace(
        1, 1,
        0, 1,
        0, 0
    );
    CHECK( linear::Projection( vector, subspace ) == linear::Matrix< 3, 1 >(
            2,
            3,
            0
        )
    );
}

TEST_CASE( "ProjectionMatrix" )
{

    CHECK( linear::ProjectionMatrix(
        linear::Matrix< 3, 2 >(
            1, 1,
            0, 1,
            0, 0
        )
    ) == linear::Matrix< 3, 3 >(
            1, 0, 0,
            0, 1, 0,
            0, 0, 0
        )
    );

    CHECK( linear::ProjectionMatrix(
        linear::Matrix< 3, 2 >(
            1, 1,
            1, 1,
            0, 1
        )
    ) == linear::Matrix< 3, 3 >(
            0.5, 0.5, 0,
            0.5, 0.5, 0,
            0,   0,   1
        )
    );
}
