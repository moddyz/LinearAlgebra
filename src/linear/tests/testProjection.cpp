#include <catch2/catch.hpp>

#include <linear/projection.h>

TEST_CASE( "Projection" )
{
    linear::Matrix< 3, 1 > vector(
        2.0f,
        3.0f,
        4.0f
    );
    linear::Matrix< 3, 2 > subspace(
        1.0f, 1.0f,
        0.0f, 1.0f,
        0.0f, 0.0f
    );
    CHECK( linear::Projection( vector, subspace ) == linear::Matrix< 3, 1 >(
            2.0f,
            3.0f,
            0.0f
        )
    );
}

TEST_CASE( "ProjectionMatrix" )
{

    CHECK( linear::ProjectionMatrix(
        linear::Matrix< 3, 2 >(
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f
        )
    ) == linear::Matrix< 3, 3 >(
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f
        )
    );

    CHECK( linear::ProjectionMatrix(
        linear::Matrix< 3, 2 >(
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f
        )
    ) == linear::Matrix< 3, 3 >(
            0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            0.0f, 0.0f, 1.0f
        )
    );
}
