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

TEST_CASE( "Matrix_RowCount_ColumnCount_EntryCount" )
{
    constexpr size_t rows = 5, cols = 7;
    CHECK( LinearAlgebra::Matrix< rows, cols >::RowCount() == rows );
    CHECK( LinearAlgebra::Matrix< rows, cols >::ColumnCount() == cols );
    CHECK( LinearAlgebra::Matrix< rows, cols >::EntryCount() == rows * cols );
}

TEST_CASE( "Matrix_Identity" )
{
    constexpr size_t                    rows = 5, cols = 5;
    LinearAlgebra::Matrix< rows, cols > matrix = LinearAlgebra::Matrix< rows, cols >::Identity();
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

TEST_CASE( "Matrix_HasNans" )
{
    constexpr size_t                    rows = 5, cols = 5;
    LinearAlgebra::Matrix< rows, cols > matrix;
    CHECK( !matrix.HasNans() );
    matrix( 0, 5 ) = NAN;
    CHECK( matrix.HasNans() );
}

