#include <boost/type_traits/is_enum.hpp>

enum E1 { a, b, c };
enum class E2 { a, b, c };

static_assert(boost::is_enum<E1>::value, "regular enum");
static_assert(boost::is_enum<E2>::value, "new enums");
