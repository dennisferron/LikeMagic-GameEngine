
#include <boost/spirit/include/qi.hpp>

namespace IoDbg {


template <typename Iterator>
struct StringUnescapeParser : boost::spirit::qi::grammar<Iterator, std::string()>
{
    StringUnescapeParser() : StringUnescapeParser::base_type(start)
    {
        unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                      ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
                      ("\\\'", '\'')("\\\"", '\"')("\\0", '\0')("\\z", 26)
            ;

        unesc_str = *(   unesc_char | (boost::spirit::qi::print - boost::spirit::qi::char_("\\\"")) | ( boost::spirit::qi::lit("\\x") > boost::spirit::qi::hex > boost::spirit::qi::lit(";") )  );
        start %= unesc_str;
    }

    boost::spirit::qi::rule<Iterator, std::string()> start;
    boost::spirit::qi::rule<Iterator, std::string()> unesc_str;
    boost::spirit::qi::symbols<char const, char const> unesc_char;
};

}
