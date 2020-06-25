#pragma once

/// \file linear/linear.h
///
/// LinearAlgebra: A general-purpose header-only linear algebra library.

/// \def LINEAR_NS
///
/// The namespace hosting all the symbols in the LinearAlgebra library.
#define LINEAR_NS linear

/// \def LINEAR_NS_USING
///
/// Convenience using directive for LINEAR_NS.
#define LINEAR_NS_USING using namespace LINEAR_NS;

/// \def LINEAR_NS_OPEN
///
/// Used throughout the library to open the LinearAlgebra namespace scope.
#define LINEAR_NS_OPEN                                                                                                 \
    namespace LINEAR_NS                                                                                                \
    {
/// \def LINEAR_NS_CLOSE
///
/// Used throughout the library to close the LinearAlgebra namespace scope.
#define LINEAR_NS_CLOSE }
