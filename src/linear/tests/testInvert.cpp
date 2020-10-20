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
        1.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f,
        2.0f, 3.0f, 1.0f
    ) );

    CHECK_INVERSE( linear::Matrix< 4, 4 >(
        1.0f, 7.0f, 0.25f, 8.0f,
        0.0f, 5.0f, 8.0f, 9.0f,
        2.0f, -3.0f, 1.0f, 1.3f,
        8.0f, 1.0f, 2.0f, 1.3f
    ) );

    CHECK_INVERSE( linear::Matrix< 5, 5 >(
        1.0f, 7.0f, 0.0f,  8.0f,   0.0f,
        5.0f, 8.0f, 9.0f,  2.0f,  -3.0f,
        9.0f, 0.0f, 1.0f,  23.0f, -2.0f,
        0.0f, 1.0f, 1.0f,  0.0f,  -9.0f,
        1.0f, 8.0f, 1.0f,  2.0f,   1.3f
    ) );
}
