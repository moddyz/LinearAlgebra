#include <catch2/catch.hpp>

#include <linear/matrix.h>

//
// Constructors.
//

TEST_CASE( "Matrix_DefaultConstructor" )
{
    linear::Matrix< 2, 2 > matrix;
    CHECK( matrix[ 0 ] == 0 );
    CHECK( matrix[ 1 ] == 0 );
    CHECK( matrix[ 2 ] == 0 );
    CHECK( matrix[ 3 ] == 0 );
}

TEST_CASE( "Matrix_DefaultConstructor_constexpr" )
{
    constexpr linear::Matrix< 2, 2 > matrix;
    static_assert( matrix[ 0 ] == 0 );
    static_assert( matrix[ 1 ] == 0 );
    static_assert( matrix[ 2 ] == 0 );
    static_assert( matrix[ 3 ] == 0 );
}

TEST_CASE( "Matrix_InitializerListConstructor" )
{
    // Runtime check.
    linear::Matrix< 2, 2 > matrix( 2, 0, 0, 2 );
    CHECK( matrix( 0, 0 ) == 2 );
    CHECK( matrix( 0, 1 ) == 0 );
    CHECK( matrix( 1, 0 ) == 0 );
    CHECK( matrix( 1, 1 ) == 2 );
}

TEST_CASE( "Matrix_InitializerListConstructor_constexpr" )
{
    // Compile-time check.
    constexpr linear::Matrix< 2, 2 > matrix( 2, 0, 0, 2 );
    static_assert( matrix( 0, 0 ) == 2 );
    static_assert( matrix( 0, 1 ) == 0 );
    static_assert( matrix( 1, 0 ) == 0 );
    static_assert( matrix( 1, 1 ) == 2 );
}

//
// Logical operators.
//

TEST_CASE( "Matrix_Equality" )
{
    linear::Matrix< 2, 2 > matrixA( 2, 0, 0, 2 );
    linear::Matrix< 2, 2 > matrixB( 2, 0, 0, 2 );
    linear::Matrix< 2, 2 > matrixC( 3, 0, 0, 3 );
    CHECK( matrixA == matrixB );
    CHECK( matrixA != matrixC );
}

TEST_CASE( "Matrix_Equality_constexpr" )
{
    constexpr linear::Matrix< 2, 2 > matrixA( 2, 0, 0, 2 );
    constexpr linear::Matrix< 2, 2 > matrixB( 2, 0, 0, 2 );
    constexpr linear::Matrix< 2, 2 > matrixC( 3, 0, 0, 3 );
    static_assert( matrixA == matrixB );
    static_assert( matrixA != matrixC );
}

//
// Arithmetic operators.
//

TEST_CASE( "Matrix_Addition" )
{
    linear::Matrix< 2, 2 > matrixA( 1, 0, 0, 1 );
    linear::Matrix< 2, 2 > matrixB( 0, 2, 2, 0 );
    linear::Matrix< 2, 2 > matrixC = matrixA + matrixB;
    CHECK( matrixC == linear::Matrix< 2, 2 >( 1, 2, 2, 1 ) );
}

TEST_CASE( "Matrix_Addition_constexpr" )
{
    constexpr linear::Matrix< 2, 2 > matrixA( 1, 0, 0, 1 );
    constexpr linear::Matrix< 2, 2 > matrixB( 0, 2, 2, 0 );
    constexpr linear::Matrix< 2, 2 > matrixC = matrixA + matrixB;
    static_assert( matrixC == linear::Matrix< 2, 2 >( 1, 2, 2, 1 ) );
}

TEST_CASE( "Matrix_Subtraction" )
{
    linear::Matrix< 2, 2 > matrixA( 1, 3, 3, 1 );
    linear::Matrix< 2, 2 > matrixB( 0, 2, 2, 3 );
    linear::Matrix< 2, 2 > matrixC = matrixA - matrixB;
    CHECK( matrixC == linear::Matrix< 2, 2 >( 1, 1, 1, -2 ) );
}

TEST_CASE( "Matrix_Subtraction_constexpr" )
{
    constexpr linear::Matrix< 2, 2 > matrixA( 1, 3, 3, 1 );
    constexpr linear::Matrix< 2, 2 > matrixB( 0, 2, 2, 3 );
    constexpr linear::Matrix< 2, 2 > matrixC = matrixA - matrixB;
    static_assert( matrixC == linear::Matrix< 2, 2 >( 1, 1, 1, -2 ) );
}

TEST_CASE( "Matrix_ScalarMultiplication" )
{
    linear::Matrix< 2, 2 > matrixA( 1, 0, 0, 1 );

    // Matrix-Scalar.
    linear::Matrix< 2, 2 > matrixB = matrixA * 2.5f;
    CHECK( matrixB == linear::Matrix< 2, 2 >( 2.5, 0, 0, 2.5 ) );

    // Scalar-Matrix.
    linear::Matrix< 2, 2 > matrixC = 2.5f * matrixA;
    CHECK( matrixC == linear::Matrix< 2, 2 >( 2.5, 0, 0, 2.5 ) );
}

TEST_CASE( "Matrix_ScalarMultiplication_constexpr" )
{
    constexpr linear::Matrix< 2, 2 > matrixA( 1, 0, 0, 1 );

    // Matrix-Scalar.
    constexpr linear::Matrix< 2, 2 > matrixB = matrixA * 2.5f;
    static_assert( matrixB == linear::Matrix< 2, 2 >( 2.5, 0, 0, 2.5 ) );

    // Scalar-Matrix.
    constexpr linear::Matrix< 2, 2 > matrixC = 2.5f * matrixA;
    static_assert( matrixC == linear::Matrix< 2, 2 >( 2.5, 0, 0, 2.5 ) );
}

TEST_CASE( "Matrix_ScalarDivision" )
{
    linear::Matrix< 2, 2 > matrixA( 2.5, 0, 0, 2.5 );
    linear::Matrix< 2, 2 > matrixB = matrixA / 2.5f;
    CHECK( matrixB == linear::Matrix< 2, 2 >( 1, 0, 0, 1 ) );
}

TEST_CASE( "Matrix_ScalarDivision_constexpr" )
{
    constexpr linear::Matrix< 2, 2 > matrixA( 2.5, 0, 0, 2.5 );
    constexpr linear::Matrix< 2, 2 > matrixB = matrixA / 2.5f;
    static_assert( matrixB == linear::Matrix< 2, 2 >( 1, 0, 0, 1 ) );
}

TEST_CASE( "Matrix_AdditionAssignment" )
{
    linear::Matrix< 2, 2 > matrixA( 1, 0, 0, 1 );
    linear::Matrix< 2, 2 > matrixB( 0, 2, 2, 0 );
    matrixB += matrixA;
    CHECK( matrixB == linear::Matrix< 2, 2 >( 1, 2, 2, 1 ) );
}

TEST_CASE( "Matrix_SubtractionAssignment" )
{
    linear::Matrix< 2, 2 > matrixA( 1, 3, 3, 1.5 );
    linear::Matrix< 2, 2 > matrixB( 0, 2, 2, 3 );
    matrixA -= matrixB;
    CHECK( matrixA == linear::Matrix< 2, 2 >( 1, 1, 1, -1.5 ) );
}

TEST_CASE( "Matrix_ScalarMultiplicationAssignment" )
{
    linear::Matrix< 2, 2 > matrixA( 1, 0, 0, 1 );
    matrixA *= 2.5f;
    CHECK( matrixA == linear::Matrix< 2, 2 >( 2.5, 0, 0, 2.5 ) );
}

TEST_CASE( "Matrix_ScalarDivisionAssignment" )
{
    linear::Matrix< 2, 2 > matrixA( 2.5, 0, 0, 2.5 );
    matrixA /= 2.5f;
    CHECK( matrixA == linear::Matrix< 2, 2 >( 1, 0, 0, 1 ) );
}

//
// Matrix extraction functionality.
//

TEST_CASE( "Matrix_Slice" )
{
    linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    linear::Matrix< 2, 2 > slice  = matrix.Slice< 0, 0, 1, 1 >();
    CHECK( slice == linear::Matrix< 2, 2 >::Identity() );
}

TEST_CASE( "Matrix_Slice_constexpr" )
{
    constexpr linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    constexpr linear::Matrix< 2, 2 > slice  = matrix.Slice< 0, 0, 1, 1 >();
    static_assert( slice == linear::Matrix< 2, 2 >::Identity() );
}

//
// Linear algebra functionality.
//

TEST_CASE( "Matrix_Multiplication" )
{
    using MatrixT   = linear::Matrix< 2, 2 >;
    MatrixT matrixA = MatrixT::Identity();
    MatrixT matrixB = MatrixT::Identity();
    CHECK( matrixA * matrixB == MatrixT::Identity() );
}

TEST_CASE( "Matrix_Multiplication_constexpr" )
{
    using MatrixT             = linear::Matrix< 2, 2 >;
    constexpr MatrixT matrixA = MatrixT::Identity();
    constexpr MatrixT matrixB = MatrixT::Identity();
    static_assert( matrixA * matrixB == MatrixT::Identity() );
}

TEST_CASE( "Matrix_Identity" )
{
    using MatrixT  = linear::Matrix< 3, 3 >;
    MatrixT matrix = MatrixT::Identity();
    CHECK( matrix == MatrixT( 1, 0, 0, 0, 1, 0, 0, 0, 1 ) );
}

TEST_CASE( "Matrix_Identity_constexpr" )
{
    using MatrixT            = linear::Matrix< 3, 3 >;
    constexpr MatrixT matrix = MatrixT::Identity();
    static_assert( matrix == MatrixT( 1, 0, 0, 0, 1, 0, 0, 0, 1 ) );
}

TEST_CASE( "Matrix_SetIdentity" )
{
    using MatrixT = linear::Matrix< 3, 3 >;
    MatrixT matrix;
    matrix.SetIdentity();
    CHECK( matrix == MatrixT( 1, 0, 0, 0, 1, 0, 0, 0, 1 ) );
}
//
// Custom functionality.
//

TEST_CASE( "Matrix_RowCount_ColumnCount_EntryCount" )
{
    // Runtime check.
    CHECK( linear::Matrix< 5, 5 >::RowCount() == 5 );
    CHECK( linear::Matrix< 2, 7 >::ColumnCount() == 7 );
    CHECK( linear::Matrix< 3, 4 >::EntryCount() == 12 );
}

TEST_CASE( "Matrix_RowCount_ColumnCount_EntryCount_constexpr" )
{
    // Compile-time check.
    static_assert( linear::Matrix< 5, 5 >::RowCount() == 5 );
    static_assert( linear::Matrix< 2, 7 >::ColumnCount() == 7 );
    static_assert( linear::Matrix< 3, 4 >::EntryCount() == 12 );
}

TEST_CASE( "Matrix_HasNans" )
{
    constexpr size_t             rows = 5, cols = 5;
    linear::Matrix< rows, cols > matrix;
    CHECK( !matrix.HasNans() );
    matrix( 0, 0 ) = NAN;
    CHECK( matrix.HasNans() );
}

