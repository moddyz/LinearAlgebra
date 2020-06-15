#include <catch2/catch.hpp>

#include <linear/multiply.h>

TEST_CASE( "Multiply" )
{
    using MatrixT   = linear::Matrix< 2, 2 >;
    MatrixT matrixA = MatrixT::Identity();
    MatrixT matrixB = MatrixT::Identity();
    CHECK( linear::Multiply( matrixA, matrixB ) == MatrixT::Identity() );
}

TEST_CASE( "Multiply_constexpr" )
{
    using MatrixT             = linear::Matrix< 2, 2 >;
    constexpr MatrixT matrixA = MatrixT::Identity();
    constexpr MatrixT matrixB = MatrixT::Identity();
    static_assert( linear::Multiply( matrixA, matrixB ) == MatrixT::Identity() );
}
