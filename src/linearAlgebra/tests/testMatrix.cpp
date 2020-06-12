//
// This file is auto-generated, please do not modify directly!
//

#include <catch2/catch.hpp>

#include <linearAlgebra/matrix.h>

TEST_CASE( "Matrix_DefaultConstructor" )
{
    constexpr size_t                    rows = 5, cols = 5;
    LinearAlgebra::Matrix< rows, cols > matrix;
    for ( size_t row = 0; row < rows; ++row )
    {
        for ( size_t col = 0; col < cols; ++col )
        {
            CHECK( matrix( row, col ) == 0 );
        }
    }
}

TEST_CASE( "Matrix_GetRowSize_GetColumnSize" )
{
    constexpr size_t rows = 5, cols = 7;
    CHECK( LinearAlgebra::Matrix< rows, cols >::GetRowSize() == rows );
    CHECK( LinearAlgebra::Matrix< rows, cols >::GetColumnSize() == cols );
}

TEST_CASE( "Matrix_GetIdentity" )
{
    constexpr size_t                    rows = 5, cols = 5;
    LinearAlgebra::Matrix< rows, cols > matrix = LinearAlgebra::Matrix< rows, cols >::GetIdentity();
    for ( size_t row = 0; row < rows; ++row )
    {
        for ( size_t col = 0; col < cols; ++col )
        {
            if ( row == col )
            {
                CHECK( matrix( row, col ) == 1 );
            }
            else
            {
                CHECK( matrix( row, col ) == 0 );
            }
        }
    }
}

