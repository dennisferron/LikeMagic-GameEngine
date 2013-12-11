
#define DECL_STRUCTS
#define QI_DECL
#include "Rules/StringEscaper.hpp"
#undef QI_DECL
#undef DECL_STRUCTS

using namespace IoDbg;
using namespace IoDbg::Rules;
using namespace IoDbg::Rules::qi_rules;

struct StringUnescapeParser : boost::spirit::qi::grammar<Iterator, std::string()>
{
    StringUnescapeParser() : StringUnescapeParser::base_type(start)
    {
        start = esc_str;
    }

    boost::spirit::qi::rule<Iterator, std::string()> start;
};

namespace IoDbg {

boost::spirit::qi::grammar<std::string::const_iterator, std::string()>* string_unescape_parse_grammar()
{
#define QI_DEFN
    #include "Rules/StringEscaper.hpp"
#undef QI_DEFN
    return new StringUnescapeParser();
}

}
