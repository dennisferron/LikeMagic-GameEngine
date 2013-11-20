
#include "SpiritMacros.hpp"

// Do NOT define #pragma once in rules headers.

SPIRIT_STRUCT((IoDbg)(Rules),
    SourceDirectoriesSearched,
        (std::string, directory_list),
    src_dirs_srch,
        qi::lit("Source directories searched: ") > *qi::char_,
        karma::lit("Source directories searched: ") << karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    ReadingSymbols,
        (std::string, message),
    reading_symbols,
        qi::lit("Reading ") > +qi::char_,
        karma::lit("Reading ") << karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    RawStr,
        (std::string, value),
    raw_str,
        raw_str, //qi::lit("") >> +qi::char_,
        karma::string;
)

SPIRIT_STRUCT((IoDbg)(Rules),
    SignalReceived,
        (std::string, msg),
    signal_received,
        qi::lit("Program received signal ") > +qi::char_,
        karma::lit("Program received signal ") << karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    SquareBracketMsg,
        (std::string, msg),
    square_bracket_msg,
        qi::lit('[') >> *(qi::char_ - qi::char_(']')) >> qi::lit(']'),
        karma::lit("[") << karma::string << "]"
)

#ifdef DECL_STRUCTS
namespace IoDbg { namespace Rules {

typedef boost::variant
<
    Rules::ReadingSymbols,
    Rules::Banner,
    Rules::SquareBracketMsg,
    Rules::SignalReceived,
    Rules::SourceDirectoriesSearched,
    Rules::RawStr
> GdbUnactionableType;

}}
#endif

SPIRIT_RULE((IoDbg)(Rules), GdbUnactionableType,
    unactionable_variant,
        banner | reading_symbols | square_bracket_msg | signal_received | src_dirs_srch | raw_str,
        banner | reading_symbols | square_bracket_msg | signal_received | src_dirs_srch | raw_str
)

SPIRIT_STRUCT((IoDbg)(Rules),
    GdbUnactionable,
        (GdbUnactionableType, value),
    unactionable,
        unactionable_variant,
        unactionable_variant
)

