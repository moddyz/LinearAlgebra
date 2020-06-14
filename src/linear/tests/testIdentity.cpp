#include <catch2/catch.hpp>

#include <linear/identity.h>

TEST_CASE( "GetIdentity" )
{
    using MatrixT = linear::Matrix< 3, 3 >;
    MatrixT matrix = linear::GetIdentity< MatrixT >();
    CHECK( matrix == MatrixT( 1, 0, 0, 0, 1, 0, 0, 0, 1 ) );
}

TEST_CASE( "GetIdentity_constexpr" )
{
    using MatrixT = linear::Matrix< 3, 3 >;
    constexpr MatrixT matrix = linear::GetIdentity< MatrixT >();
    static_assert( matrix == MatrixT( 1, 0, 0, 0, 1, 0, 0, 0, 1 ) );
}

TEST_CASE( "SetIdentity" )
{
    using MatrixT = linear::Matrix< 3, 3 >;
    MatrixT matrix;
    linear::SetIdentity( matrix );
    CHECK( matrix == MatrixT( 1, 0, 0, 0, 1, 0, 0, 0, 1 ) );
}
