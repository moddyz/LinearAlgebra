//
// This file is auto-generated, please do not modify directly!
//

#include <catch2/catch.hpp>

#include <linear/matrix.h>

TEST_CASE( "Matrix_DefaultConstructor" )
{
    constexpr size_t             rows = 5, cols = 5;
    linear::Matrix< rows, cols > matrix;
    for ( size_t row = 0; row < rows; ++row )
    {
        for ( size_t col = 0; col < cols; ++col )
        {
            CHECK( matrix( row, col ) == 0 );
        }
    }
}

TEST_CASE( "Matrix_InitializerListConstructor" )
{
    linear::Matrix< 2, 2 > matrix(
        2, 0,
        0, 2
    );
    CHECK( matrix( 0, 0 ) == 2 );
    CHECK( matrix( 0, 1 ) == 0 );
    CHECK( matrix( 1, 0 ) == 0 );
    CHECK( matrix( 1, 1 ) == 2 );
}

TEST_CASE( "Matrix_RowCount_ColumnCount_EntryCount" )
{
    constexpr size_t rows = 5, cols = 7;
    CHECK( linear::Matrix< rows, cols >::RowCount() == rows );
    CHECK( linear::Matrix< rows, cols >::ColumnCount() == cols );
    CHECK( linear::Matrix< rows, cols >::EntryCount() == rows * cols );
}

TEST_CASE( "Matrix_Identity" )
{
    constexpr size_t             rows = 5, cols = 5;
    linear::Matrix< rows, cols > matrix = linear::Matrix< rows, cols >::Identity();
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
    constexpr size_t             rows = 5, cols = 5;
    linear::Matrix< rows, cols > matrix;
    CHECK( !matrix.HasNans() );
    matrix( 0, 5 ) = NAN;
    CHECK( matrix.HasNans() );
}

