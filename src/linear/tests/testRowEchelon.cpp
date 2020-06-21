#include <catch2/catch.hpp>

#include <linear/rowEchelon.h>

TEST_CASE( "Matrix_RowEchelonForm" )
{
    using MatrixT = linear::Matrix< 3, 4 >;
    MatrixT matrix(
        1, 2, 2, 2,
        2, 4, 6, 8,
        3, 6, 8, 10
    );

    CHECK( linear::RowEchelonForm( matrix ) == MatrixT(
        1, 2, 2, 2,
        0, 0, 2, 4,
        0, 0, 0, 0
    ) );
}
