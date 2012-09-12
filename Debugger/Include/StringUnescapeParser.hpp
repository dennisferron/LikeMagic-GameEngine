
#include <boost/spirit/include/qi.hpp>

namespace Iocaste { namespace Debugger {

namespace qi = boost::spirit::qi;

template <typename Iterator>
struct StringUnescapeParser : qi::grammar<Iterator, std::string()>
{
    StringUnescapeParser() : StringUnescapeParser::base_type(start)
    {
        unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                      ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
                      ("\\\'", '\'')("\\\"", '\"')("\\0", '\0')("\\z", 26)
            ;

        unesc_str = *(   unesc_char | (qi::print - qi::char_("\\\"")) | ( qi::lit("\\x") > qi::hex > qi::lit(";") )  );
        start %= unesc_str;
    }

    qi::rule<Iterator, std::string()> start;
    qi::rule<Iterator, std::string()> unesc_str;
    qi::symbols<char const, char const> unesc_char;
};

}}
