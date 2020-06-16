#include <catch2/catch.hpp>

#include <linear/invert.h>
#include <linear/multiply.h>

#include <iostream>

TEST_CASE( "Matrix_Invert" )
{
    using MatrixT = linear::Matrix< 3, 3 >;
    MatrixT matrix = MatrixT(
        3, 2, 1,
        2, 3, 8,
        1, 3, 3
    );

    MatrixT inverse;
    CHECK( linear::Invert( matrix, inverse ) );
    std::cout << inverse << std::endl;

    CHECK( linear::Multiply( matrix, inverse ) == MatrixT::Identity() );
}
