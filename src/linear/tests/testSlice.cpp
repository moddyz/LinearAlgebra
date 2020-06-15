#include <catch2/catch.hpp>

#include <linear/slice.h>

TEST_CASE( "Slice" )
{
    linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    linear::Matrix< 2, 2 > slice  = linear::Slice< 0, 0, 2, 2 >( matrix);
    CHECK( slice == linear::Matrix< 2, 2 >::Identity() );
}

TEST_CASE( "Slice_constexpr" )
{
    constexpr linear::Matrix< 3, 3 > matrix = linear::Matrix< 3, 3 >::Identity();
    constexpr linear::Matrix< 2, 2 > slice  = linear::Slice< 0, 0, 2, 2 >( matrix );
    static_assert( slice == linear::Matrix< 2, 2 >::Identity() );
}

