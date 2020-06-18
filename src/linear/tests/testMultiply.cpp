#include <catch2/catch.hpp>

#include <linear/multiply.h>

TEST_CASE( "Multiply" )
{
    using MatrixT   = linear::Matrix< 2, 2 >;
    MatrixT matrixA = MatrixT::Identity();
    MatrixT matrixB = MatrixT::Identity();
    CHECK( linear::Multiply( matrixA, matrixB ) == MatrixT::Identity() );

    CHECK( linear::Multiply( linear::Matrix< 3, 3 >(
        1, 0, 0,
        1, 1, 1,
        0, 0, 1
    ), linear::Matrix< 3, 3 >(
        2,   0, 0,
        0,   3, 0,
        1.5, 0, 4
    ) )  == linear::Matrix< 3, 3 >(
        2,   0, 0,
        3.5, 3, 4,
        1.5, 0, 4
    ) );

    CHECK( linear::Multiply( linear::Matrix< 3, 1 >(
        1, 2, 3
    ), linear::Matrix< 1, 3 >(
        2,
        3,
        1.5
    ) ) == linear::Matrix< 3, 3 >(
        2, 3, 1.5,
        4, 6, 3,
        6, 9, 4.5
    ) );
}

TEST_CASE( "Multiply_constexpr" )
{
    using MatrixT             = linear::Matrix< 2, 2 >;
    constexpr MatrixT matrixA = MatrixT::Identity();
    constexpr MatrixT matrixB = MatrixT::Identity();
    static_assert( linear::Multiply( matrixA, matrixB ) == MatrixT::Identity() );
}
