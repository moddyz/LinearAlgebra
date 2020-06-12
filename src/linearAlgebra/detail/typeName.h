#include <string_view>

#include <linearAlgebra/linearAlgebra.h>

LINEAR_ALGEBRA_NS_OPEN

/// Utility for extracing the string name of a type \p T.
///
/// From:
/// https://stackoverflow.com/questions/81870/is-it-possible-to-print-a-variables-type-in-standard-c
///
/// \tparam T the type to extract the string name from.
///
/// \return string name of the type.
template < typename T >
constexpr std::string_view _TypeName()
{
    std::string_view name, prefix, suffix;
#ifdef __clang__
    name   = __PRETTY_FUNCTION__;
    prefix = "std::string_view LinearAlgebra::_TypeName() [T = ";
    suffix = "]";
#elif defined( __GNUC__ )
    name   = __PRETTY_FUNCTION__;
    prefix = "constexpr std::string_view LinearAlgebra::_TypeName() [with T = ";
    suffix = "; std::string_view = std::basic_string_view<char>]";
#elif defined( _MSC_VER )
    name   = __FUNCSIG__;
    prefix = "class std::basic_string_view<char,struct std::char_traits<char> > __cdecl LinearAlgebra::_TypeName<";
    suffix = ">(void)";
#endif
    name.remove_prefix( prefix.size() );
    name.remove_suffix( suffix.size() );
    return name;
}

LINEAR_ALGEBRA_NS_CLOSE
