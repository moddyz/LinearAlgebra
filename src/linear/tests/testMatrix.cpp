//
// This file is auto-generated, please do not modify directly!
//

#include <catch2/catch.hpp>

#include <linear/matrix.h>

TEST_CASE( "Matrix_DefaultConstructor" )
{
    // Runtime check.
    linear::Matrix< 2, 2 > matrix;
    CHECK( matrix[ 0 ] == 0 );
    CHECK( matrix[ 1 ] == 0 );
    CHECK( matrix[ 2 ] == 0 );
    CHECK( matrix[ 3 ] == 0 );

    // Compile-time check.
    constexpr linear::Matrix< 2, 2 > constMatrix;
    static_assert( constMatrix[ 0 ] == 0 );
    static_assert( constMatrix( 0, 1 ) == 0 );
}

TEST_CASE( "Matrix_InitializerListConstructor" )
{
    // Runtime check.
    linear::Matrix< 2, 2 > matrix( 2, 0, 0, 2 );
    CHECK( matrix( 0, 0 ) == 2 );
    CHECK( matrix( 0, 1 ) == 0 );
    CHECK( matrix( 1, 0 ) == 0 );
    CHECK( matrix( 1, 1 ) == 2 );

    // Compile-time check.
    constexpr linear::Matrix< 2, 2 > constMatrix( 2, 0, 0, 2 );
    static_assert( constMatrix( 0, 0 ) == 2 );
    static_assert( constMatrix( 0, 1 ) == 0 );
    static_assert( constMatrix( 1, 0 ) == 0 );
    static_assert( constMatrix( 1, 1 ) == 2 );
}

TEST_CASE( "Matrix_RowCount_ColumnCount_EntryCount" )
{
    // Runtime check.
    CHECK( linear::Matrix< 5, 5 >::RowCount() == 5 );
    CHECK( linear::Matrix< 2, 7 >::ColumnCount() == 7 );
    CHECK( linear::Matrix< 3, 4 >::EntryCount() == 12 );

    // Compile-time check.
    static_assert( linear::Matrix< 5, 5 >::RowCount() == 5 );
    static_assert( linear::Matrix< 2, 7 >::ColumnCount() == 7 );
    static_assert( linear::Matrix< 3, 4 >::EntryCount() == 12 );
}

TEST_CASE( "Matrix_Equality" )
{
    linear::Matrix< 2, 2 > matrixA( 2, 0, 0, 2 );
    linear::Matrix< 2, 2 > matrixB( 2, 0, 0, 2 );
    linear::Matrix< 2, 2 > matrixC( 3, 0, 0, 3 );
    CHECK( matrixA == matrixB );
    CHECK( matrixA != matrixC );

    constexpr linear::Matrix< 2, 2 > constMatrixA( 2, 0, 0, 2 );
    constexpr linear::Matrix< 2, 2 > constMatrixB( 2, 0, 0, 2 );
    constexpr linear::Matrix< 2, 2 > constMatrixC( 3, 0, 0, 3 );
    static_assert( constMatrixA == constMatrixB );
    static_assert( constMatrixA != constMatrixC );
}

TEST_CASE( "Matrix_Addition" )
{
    linear::Matrix< 2, 2 > matrixA( 1, 0, 0, 1 );
    linear::Matrix< 2, 2 > matrixB( 0, 2, 2, 0 );
    linear::Matrix< 2, 2 > matrixC = matrixA + matrixB;
    CHECK( matrixC == linear::Matrix< 2, 2 >( 1, 2, 2, 1 ) );
}

TEST_CASE( "Matrix_Identity" )
{
    linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    CHECK( matrix == linear::Matrix< 3, 3 >( 1, 0, 0, 0, 1, 0, 0, 0, 1 ) );
}

TEST_CASE( "Matrix_HasNans" )
{
    constexpr size_t             rows = 5, cols = 5;
    linear::Matrix< rows, cols > matrix;
    CHECK( !matrix.HasNans() );
    matrix( 0, 5 ) = NAN;
    CHECK( matrix.HasNans() );
}

