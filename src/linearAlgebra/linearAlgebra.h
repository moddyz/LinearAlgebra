#pragma once

/// \file linearAlgebra/linearAlgebra.h
///
/// LinearAlgebra: A general-purpose header-only linear algebra library.

/// \def LINEAR_ALGEBRA_NS
///
/// The namespace hosting all the symbols in the LinearAlgebra library.
#define LINEAR_ALGEBRA_NS LinearAlgebra

/// \def LINEAR_ALGEBRA_NS_USING
///
/// Convenience using directive for LINEAR_ALGEBRA_NS.
#define LINEAR_ALGEBRA_NS_USING using namespace LINEAR_ALGEBRA_NS;

/// \def LINEAR_ALGEBRA_NS_OPEN
///
/// Used throughout the library to open the LinearAlgebra namespace scope.
#define LINEAR_ALGEBRA_NS_OPEN namespace LINEAR_ALGEBRA_NS {

/// \def LINEAR_ALGEBRA_NS_CLOSE
///
/// Used throughout the library to close the LinearAlgebra namespace scope.
#define LINEAR_ALGEBRA_NS_CLOSE }
