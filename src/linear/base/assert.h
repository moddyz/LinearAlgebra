#pragma once

#include <linear/linear.h>

#include <stdarg.h>

/// \file base/assert.h
///
/// Assertion utility for printing out failure location when an expression wrapped with LINEAR_ALGEBRA_ASSERT( ... )
/// fails to evaluate.
///
/// In Debug builds, LINEAR_ALGEBRA_ASSERT macro will print the stacktrace when the input expression evaluates to false.
/// In Release builds, the LINEAR_ALGEBRA_ASSERT macro will be pre-processed away in Release builds.

/// \def LINEAR_ALGEBRA_ASSERT( expr )
/// Asserts that the expression \p expr is \em true in debug builds. If \p expr evalutes \em false,
/// an error message will be printed with contextual information such as the source code location.
///
/// In release builds, this is compiled out.
#ifdef LINEAR_ALGEBRA_DEBUG
#define LINEAR_ALGEBRA_ASSERT( expr )                                                                                  \
    if ( !( expr ) )                                                                                                   \
    {                                                                                                                  \
        LINEAR_ALGEBRA_NS::_Assert( #expr, __FILE__, __LINE__ );                                                       \
    }
#else
#define LINEAR_ALGEBRA_ASSERT( expr, ... ) void()
#endif

/// \def LINEAR_ALGEBRA_ASSERT_MSG( expr, format, ... )
/// Similar to \ref LINEAR_ALGEBRA_ASSERT, with the addition of a formatted message when the expression \p expr fails to
/// evaluate in debug builds.
#ifdef LINEAR_ALGEBRA_DEBUG
#define LINEAR_ALGEBRA_ASSERT_MSG( expr, format, ... )                                                                 \
    if ( !( expr ) )                                                                                                   \
    {                                                                                                                  \
        LINEAR_ALGEBRA_NS::_Assert( #expr, __FILE__, __LINE__ );                                                       \
        fprintf( stderr, format, ##__VA_ARGS__ );                                                                      \
    }
#else
#define LINEAR_ALGEBRA_ASSERT_MSG( expr, format, ... ) void()
#endif

LINEAR_ALGEBRA_NS_OPEN

/// Not intended to be used directly, \ref LINEAR_ALGEBRA_ASSERT instead.
inline void _Assert( const char* i_expression, const char* i_file, size_t i_line )
{
    fprintf( stderr, "Assertion failed for expression: %s, at %s:%lu\n", i_expression, i_file, i_line );
}

LINEAR_ALGEBRA_NS_CLOSE
