#pragma once

#include <linear/linear.h>

#include <linear/base/log.h>

#include <stdarg.h>

/// \file base/diagnostic.h
///
/// Diagnostic utilities.

/// \def LINEAR_ASSERT( expr )
///
/// Asserts that the expression \p expr is \em true in debug builds. If \p expr evalutes \em false,
/// an error message will be printed with contextual information including the failure site.
///
/// In release builds, this is compiled out.
#ifdef LINEAR_DEBUG
#define LINEAR_ASSERT( expr )                                                                                          \
    if ( !( expr ) )                                                                                                   \
    {                                                                                                                  \
        LINEAR_NS::_Assert( #expr, __FILE__, __LINE__ );                                                               \
    }
#else
#define LINEAR_ASSERT( expr, ... ) void()
#endif

/// \def LINEAR_ASSERT_MSG( expr, format, ... )
///
/// Similar to \ref LINEAR_ASSERT, with the addition of a formatted message when the expression \p expr fails to
/// evaluate in debug builds.
#ifdef LINEAR_DEBUG
#define LINEAR_ASSERT_MSG( expr, format, ... )                                                                         \
    if ( !( expr ) )                                                                                                   \
    {                                                                                                                  \
        LINEAR_NS::_Assert( #expr, __FILE__, __LINE__ );                                                               \
        LINEAR_LOG_ERROR( format, ##__VA_ARGS__ );                                                                     \
    }
#else
#define LINEAR_ASSERT_MSG( expr, format, ... ) void()
#endif

/// \def LINEAR_VERIFY( expr )
///
/// Verifies that the expression \p expr evaluates to \em true at runtime. If \p expr evalutes \em false,
/// an error message will be printed with contextual information including the failure site.
///
/// LINEAR_VERIFY is different from \ref LINEAR_ASSERT in that it does \em not get compiled out for release builds,
/// so use sparingly!
#define LINEAR_VERIFY( expr )                                                                                          \
    if ( !( expr ) )                                                                                                   \
    {                                                                                                                  \
        LINEAR_NS::_Assert( #expr, __FILE__, __LINE__ );                                                               \
    }

/// \def LINEAR_VERIFY_MSG( expr, format, ... )
///
/// Similar to \ref LINEAR_VERIFY, with the addition of a formatted message when the expression \p expr fails to
/// evaluate.
#define LINEAR_VERIFY_MSG( expr, format, ... )                                                                         \
    if ( !( expr ) )                                                                                                   \
    {                                                                                                                  \
        LINEAR_NS::_Verify( #expr, __FILE__, __LINE__ );                                                               \
        LINEAR_LOG_ERROR( format, ##__VA_ARGS__ );                                                                     \
    }

LINEAR_NS_OPEN

/// Not intended to be used directly, \ref LINEAR_ASSERT instead.
inline void _Assert( const char* i_expression, const char* i_file, int i_line )
{
    LINEAR_LOG_ERROR( "Assertion failed for expression: %s, at %s:%i\n", i_expression, i_file, i_line );
}

/// Not intended to be used directly, \ref LINEAR_VERIFY instead.
inline void _Verify( const char* i_expression, const char* i_file, int i_line )
{
    LINEAR_LOG_ERROR( "Verification failed for expression: %s, at %s:%i\n", i_expression, i_file, i_line );
}

LINEAR_NS_CLOSE
