//
// This file is auto-generated, please do not modify directly!
//

#include <catch2/catch.hpp>

#include <linearAlgebra/matrix.h>

TEST_CASE( "Matrix_DefaultConstructor" )
{
    constexpr size_t rows = 5, cols = 5;
    LinearAlgebra::Matrix< rows, cols > matrix;
    for ( size_t row = 0; row < rows; ++row )
    {
        for ( size_t col = 0; col < cols; ++col )
        {
            CHECK( matrix( row, col ) == 0 );
        }
    }
}

