
#include "SpiritMacros.hpp"

// Do NOT define #pragma once in rules headers.

#include <string>
#include "boost/variant.hpp"
#include "boost/optional.hpp"

// SPIRIT_RULE(NAMESPACE_SEQ, RTYPE, RULE_NAME, QI_EXPR, KARMA_EXPR)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    no_locals_str,
        qi::string("No locals.") | qi::string("No arguments.") | qi::string("No symbol table info available."),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    type_cast_str,
        qi::char_('(') >> *(qi::char_ - qi::char_(')')) >> qi::char_(')') >> -qi::char_(' '),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    ident,
        +(qi::alpha | qi::char_('-') | qi::char_('_')),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    file_name,
        +(qi::print -  qi::char_(':') - qi::char_(',')),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    device_name,
        +(qi::print), // for tty
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    dummy,
        +qi::char_('\xFF'),
    /* dummy %= */ karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    function_name,
        +(qi::char_ - qi::char_(' ')),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    version_number,
        +(qi::digit | qi::char_('.') | qi::char_('-')),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    program_exited_str,
        +qi::print > qi::eoi,
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    equals,
        -qi::space >> qi::char_("=") >> -qi::space,
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    up_to_last_period,
        *( qi::char_ - ( qi::lit('.')>>qi::eoi ) ),
        karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    AddressIn,
        (GdbAddress, address),
    address_in,
        address >> " in ",
        address << karma::lit(" in ")
)

SPIRIT_STRUCT((IoDbg)(Rules),
    FromModule,
        (std::string, module_name),
    from_module,
        qi::lit(" from ") >> file_name,
        karma::lit(" from ") << file_name
)

SPIRIT_STRUCT((IoDbg)(Rules),
    AtFile,
        (std::string, file_name),
    at_file,
        qi::lit(" at ") >> file_name,
        karma::lit(" at ") << file_name
)

SPIRIT_STRUCT((IoDbg)(Rules),
    NoLocals,
        (std::string, text),
    no_locals,
        no_locals_str,
        no_locals_str
)

SPIRIT_STRUCT((IoDbg)(Rules),
    GdbResponseFunctionArg,
        (std::string, name)
        (std::string, equals)
        (GdbValue, value),
    function_arg,
        ident > equals > gdb_value,
        ident << equals << gdb_value
)

SPIRIT_STRUCT((IoDbg)(Rules),
    GdbResponseFunction,
        (std::string, name)
        (std::vector<GdbResponseFunctionArg>, args),
    gdb_function,
        function_name > " (" > -(function_arg % ", ") > ")",
        function_name << " (" << -(function_arg % ", ") << ")"
)

SPIRIT_STRUCT((IoDbg)(Rules),
    TypeCast,
        (std::string, value),
    type_cast,
        type_cast_str,
        karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    VariableEquals,
        (std::string, name)
        (std::string, equals)
        (boost::optional<TypeCast>, type_cast)
        (GdbValue, value),
    variable_equals,
        ident >> equals >> -type_cast >> gdb_value,
        ident << equals << -type_cast << gdb_value
)

