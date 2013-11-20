#include "SpiritMacros.hpp"

#ifdef DECL_STRUCTS
#include <string>
#include "boost/variant.hpp"
#include "boost/optional.hpp"
#endif

SPIRIT_RULE((IoDbg)(Rules), std::string,
    quoted_string,
        qi::lit('"') >> *unesc_grammar >> qi::lit('"'),
        karma::lit("\"") << *esc_grammar << "\""
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    elipses,
        qi::string("..."),
        karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    GdbStruct,
        (std::string, contents),
    gdb_struct,
        qi::lit("{") > *(qi::char_-'}') > "}",
        karma::lit("{") << karma::string << "}"
)

SPIRIT_STRUCT((IoDbg)(Rules),
    GdbAddress,
        (std::string, hex_value),
    address,
        qi::lit("0x") > +qi::alnum,
        karma::lit("0x") << karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    ValueAsString,
        (std::string, text),
    value_as_string,
        qi::lit(" ") >> quoted_string,
        karma::lit(" ") << quoted_string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    ValueElided,
        (std::string, text),
    value_elided,
        elipses,
        karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    ValueAsFunctionPtr,
        (std::string, text),
    value_as_function_ptr,
        qi::lit(" <") > +(qi::char_-'>') > ">",
        karma::lit(" <") << karma::string << ">"
)

#ifdef DECL_STRUCTS
namespace IoDbg { namespace Rules {
    typedef boost::variant<
            int, std::string, GdbAddress, GdbStruct, ValueElided
        > GdbValue_value_type;
}}
#endif

SPIRIT_STRUCT((IoDbg)(Rules),
    GdbValue,
        (GdbValue_value_type, value)
        (boost::optional<ValueAsString>, value_as_string)
        (boost::optional<ValueAsFunctionPtr>, value_as_function_ptr),
    gdb_value,
        (address | qi::int_ | quoted_string | gdb_struct | value_elided) >> -value_as_string >> -value_as_function_ptr,
        (address | karma::int_ | quoted_string | gdb_struct | value_elided) << -value_as_string << -value_as_function_ptr
)
