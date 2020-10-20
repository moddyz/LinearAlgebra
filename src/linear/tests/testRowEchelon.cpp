#include <catch2/catch.hpp>

#include <linear/rowEchelon.h>

TEST_CASE( "Matrix_RowEchelonForm" )
{
    using MatrixT = linear::Matrix< 3, 4 >;
    MatrixT matrix(
        1.0f, 2.0f, 2.0f, 2.0f,
        2.0f, 4.0f, 6.0f, 8.0f,
        3.0f, 6.0f, 8.0f, 10.0f
    );

    CHECK( linear::RowEchelonForm( matrix ) == MatrixT(
        1.0f, 2.0f, 2.0f, 2.0f,
        0.0f, 0.0f, 2.0f, 4.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    ) );
}

TEST_CASE( "Matrix_ReducedRowEchelonForm" )
{
    using MatrixT = linear::Matrix< 3, 4 >;
    MatrixT matrix(
        1.0f, 2.0f, 2.0f, 2.0f,
        2.0f, 4.0f, 6.0f, 8.0f,
        3.0f, 6.0f, 8.0f, 10.0f
    );

    CHECK( linear::ReducedRowEchelonForm( matrix ) == MatrixT(
        1.0f, 2.0f, 0.0f, -2.0f,
        0.0f, 0.0f, 1.0f, 2.0f,
        0.0f, 0.0f, 0.0f, 0.0f
    ) );
}
