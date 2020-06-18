
#include <catch2/catch.hpp>

#include <linear/matrix.h>
#include <linear/transpose.h>

TEST_CASE( "Matrix_Transpose" )
{
    using MatrixT  = linear::Matrix< 3, 3 >;
    MatrixT matrix = MatrixT(
        1, 2, 3,
        1, 1, 1,
        2, 2, 2
    );
    CHECK( linear::Transpose( matrix ) == MatrixT(
        1, 1, 2,
        2, 1, 2,
        3, 1, 2
    ) );
}

TEST_CASE( "Matrix_Transpose_constexpr" )
{
    using MatrixT  = linear::Matrix< 3, 3 >;
    constexpr MatrixT matrix = MatrixT(
        1, 2, 3,
        1, 1, 1,
        2, 2, 2
    );
    static_assert( linear::Transpose( matrix ) == MatrixT(
        1, 1, 2,
        2, 1, 2,
        3, 1, 2
    ) );
}
