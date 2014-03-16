
#include "SpiritMacros.hpp"

/*
SPIRIT_RULE((IoDbg)(Rules), std::string,
    version_number,
        +(qi::alnum | qi::char_('.') | qi::char_('-') | qi::char_('/')),
        karma::string
)
*/

SPIRIT_RULE((IoDbg)(Rules), std::string,
    paren_expr,
        qi::char_('(') > (version_number % qi::char_(' ')) > qi::char_(')'),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    version_or_expr,
        paren_expr | version_number,
        paren_expr | version_number
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    banner_line,
        +(qi::char_ - '\n'),
        karma::string
)

SPIRIT_RULE((IoDbg)(Rules), std::string,
    banner_message,
        banner_line > *(qi::char_('\n') >> banner_line),
        karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    Banner,
        (std::string, version)
        (std::string, msg),
    banner,
        qi::lit("GNU gdb ") >> version_or_expr > banner_message > qi::lit("\n"),
        karma::lit("GNU gdb ") << version_or_expr << banner_message << karma::lit("\n")
)
