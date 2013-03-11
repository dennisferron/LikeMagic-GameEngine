
#include "StringUnescapeParser.hpp"
#include "ParseGrammars.hpp"

namespace Iocaste { namespace Debugger {

boost::spirit::qi::grammar<std::string::const_iterator, std::string()>* string_unescape_parse_grammar()
{
    return new StringUnescapeParser<std::string::const_iterator>();
}

}}
