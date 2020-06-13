#pragma once

/// \file identity.h
///
/// Operation which sets an matrix to the identity element (I).
///
/// The identity matrix has 1's down its main diagonal, and 0 for all other entries.
/// This operation can only be applied to square matrices (M X M matrices).

#include <linear/base/identityImpl.h>

LINEAR_ALGEBRA_NS_OPEN

/// Get the identity matrix for \p MatrixT.
///
/// \pre \p MatrixT must be a square.
///
/// \tparam MatrixT the matrix type.
///
/// \return the identity matrix.
template < typename MatrixT >
constexpr inline MatrixT GetIdentity()
{
    return _GetIdentity< MatrixT >();
}

/// Set the matrix \p o_matrix to the identity matrix.
///
/// \pre \p o_matrix must be a square matrix.
///
/// \tparam MatrixT the matrix type.
template < typename MatrixT >
inline void SetIdentity( MatrixT& o_matrix )
{
    o_matrix = _GetIdentity< MatrixT >();
}

LINEAR_ALGEBRA_NS_CLOSE
