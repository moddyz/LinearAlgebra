//
// This file is auto-generated, please do not modify directly!
//

#include <catch2/catch.hpp>

#include <linear/multiply.h>
#include <linear/identity.h>

TEST_CASE( "MatrixMultiplication_Identity" )
{
    using MatrixT = linear::Matrix< 2, 2 >;
    MatrixT matrixA = linear::GetIdentity< MatrixT >();
    MatrixT matrixB = linear::GetIdentity< MatrixT >();
    CHECK( linear::MatrixMultiplication( matrixA, matrixB ) == linear::GetIdentity< MatrixT >() );
}

TEST_CASE( "MatrixMultiplication_Identity_constexpr" )
{
    using MatrixT = linear::Matrix< 2, 2 >;
    constexpr MatrixT matrixA = linear::GetIdentity< MatrixT >();
    constexpr MatrixT matrixB = linear::GetIdentity< MatrixT >();
    static_assert( linear::MatrixMultiplication( matrixA, matrixB ) == linear::GetIdentity< MatrixT >() );
}
