#include <catch2/catch.hpp>

#include <linear/inverse.h>
#include <linear/multiply.h>

#include <iostream>

template < typename MatrixT >
void CHECK_INVERSE( const MatrixT& i_matrix )
{
    MatrixT inverse;
    CHECK( linear::Inverse( i_matrix, inverse ) );
    CHECK( linear::Multiply( i_matrix, inverse ) == MatrixT::Identity() );
    CHECK( linear::Multiply( inverse, i_matrix ) == MatrixT::Identity() );
}

TEST_CASE( "Matrix_Inverse" )
{
    CHECK_INVERSE( linear::Matrix< 3, 3 >(
        1, 0, 0,
        0, 5, 0,
        2, 3, 1
    ) );

    CHECK_INVERSE( linear::Matrix< 4, 4 >(
        1, 7, 0.25, 8,
        0, 5, 8, 9,
        2, -3, 1, 1.3,
        8, 1, 2, 1.3
    ) );

    CHECK_INVERSE( linear::Matrix< 5, 5 >(
        1, 7, 0,  8,   0,
        5, 8, 9,  2,  -3,
        9, 0, 1,  23, -2,
        0, 1, 1,  0,  -9,
        1, 8, 1,  2,   1.3
    ) );
}
