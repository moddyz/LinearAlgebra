#pragma once

/// \file slice.h
///
/// Matrix slice API.

#include <linear/base/matrixSlice.h>
#include <linear/linear.h>
#include <linear/matrix.h>

LINEAR_ALGEBRA_NS_OPEN

/// Extract a slice of the current matrix, specified by row and column begins and ends.
///
/// Both the begin and end indices are inclusive in the resulting slice.
/// For example, to return a slice of the upper-left 2 x 2 matrix of a 3 x 3 matrix:
/// \code{.cpp}
/// constexpr linear::Matrix< 3, 3 > matrix;
/// constexpr linear::Matrix< 2, 2 > slice = linear::Slice< 0, 0, 2, 2 >( matrix );
/// \endcode
///
/// \pre The row and column end indices must be greater or equal to their respective begin indices.
/// \pre The row and column end indices must be less than the current matrice's respective row or column counts.
///
/// \return the specified matrix slice.
template < size_t SLICE_ROW_BEGIN,
           size_t SLICE_COLUMN_BEGIN,
           size_t SLICE_ROW_END,
           size_t SLICE_COLUMN_END,
           typename SourceMatrixT,
           typename SliceT = Matrix< SLICE_ROW_END - SLICE_ROW_BEGIN,
                                     SLICE_COLUMN_END - SLICE_COLUMN_BEGIN,
                                     typename SourceMatrixT::ValueType > >
constexpr inline SliceT Slice( const SourceMatrixT& i_matrix )
{
    static_assert( SLICE_ROW_BEGIN < SLICE_ROW_END );
    static_assert( SLICE_ROW_BEGIN < SLICE_COLUMN_END );
    static_assert( SLICE_ROW_END <= SourceMatrixT::RowCount() );
    static_assert( SLICE_COLUMN_END <= SourceMatrixT::ColumnCount() );
    return _MatrixSlice< SourceMatrixT, SliceT, SLICE_ROW_BEGIN, SLICE_COLUMN_BEGIN >( i_matrix );
}

LINEAR_ALGEBRA_NS_CLOSE
