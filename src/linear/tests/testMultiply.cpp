#include <catch2/catch.hpp>

#include <linear/multiply.h>

TEST_CASE( "Multiply" )
{
    using MatrixT   = linear::Matrix< 2, 2 >;
    MatrixT matrixA = MatrixT::Identity();
    MatrixT matrixB = MatrixT::Identity();
    CHECK( linear::Multiply( matrixA, matrixB ) == MatrixT::Identity() );

    CHECK( linear::Multiply( linear::Matrix< 3, 3 >(
        1.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f,
        0.0f, 0.0f, 1.0f
    ), linear::Matrix< 3, 3 >(
        2.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f,
        1.5f, 0.0f, 4.0f
    ) )  == linear::Matrix< 3, 3 >(
        2.0f, 0.0f, 0.0f,
        3.5f, 3.0f, 4.0f,
        1.5f, 0.0f, 4.0f
    ) );

    CHECK( linear::Multiply( linear::Matrix< 3, 1 >(
        1.0f, 2.0f, 3.0f
    ), linear::Matrix< 1, 3 >(
        2.0f,
        3.0f,
        1.5f
    ) ) == linear::Matrix< 3, 3 >(
        2.0f, 3.0f, 1.5f,
        4.0f, 6.0f, 3.0f,
        6.0f, 9.0f, 4.5f
    ) );
}

TEST_CASE( "Multiply_constexpr" )
{
    using MatrixT             = linear::Matrix< 2, 2 >;
    constexpr MatrixT matrixA = MatrixT::Identity();
    constexpr MatrixT matrixB = MatrixT::Identity();
    static_assert( linear::Multiply( matrixA, matrixB ) == MatrixT::Identity() );
}
