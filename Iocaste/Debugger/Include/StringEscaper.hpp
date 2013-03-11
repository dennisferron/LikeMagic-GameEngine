#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;


#include <boost/spirit/include/karma.hpp>

namespace karma = boost::spirit::karma;

template <typename OutputIterator>
struct escaped_string
  : karma::grammar<OutputIterator, std::string(char const*)>
{
    escaped_string()
      : escaped_string::base_type(esc_str)
    {
        esc_char.add('\a', "\\a")('\b', "\\b")('\f', "\\f")('\n', "\\n")
                    ('\r', "\\r")('\t', "\\t")('\v', "\\v")('\\', "\\\\")
                    ('\'', "\\\'")('\"', "\\\"")('\0', "\\0")(26, "\\z")
            ;

        esc_str =   karma::lit(karma::_r1)
                << *(esc_char | karma::print | "\\x" << karma::hex)
                <<  karma::lit(karma::_r1)
            ;
    }

    karma::rule<OutputIterator, std::string(char const*)> esc_str;
    karma::symbols<char, char const*> esc_char;
};

namespace qi = boost::spirit::qi;

template <typename InputIterator>
struct unescaped_string
    : qi::grammar<InputIterator, std::string(char const*)>
{
    unescaped_string()
        : unescaped_string::base_type(unesc_str)
    {
        unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                      ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
                      ("\\\'", '\'')("\\\"", '\"')
            ;

        unesc_str = qi::lit(qi::_r1)
                >> *(unesc_char | qi::alnum | "\\x" >> qi::hex >> "x")
                >>  qi::lit(qi::_r1)
            ;
    }

    qi::rule<InputIterator, std::string(char const*)> unesc_str;
    qi::symbols<char const, char const> unesc_char;
};

std::string escape(std::string input)
{
    namespace karma = boost::spirit::karma;

    typedef std::back_insert_iterator<std::string> sink_type;

    std::string generated;
    sink_type sink(generated);

    std::string str("string to escape: \n\r\t\"'\x19");
    str.push_back(0);
    str.push_back(26);
    char const* quote = "'''";

    escaped_string<sink_type> g;
    if (!karma::generate(sink, g(quote), str))
    {
        std::cout << "-------------------------\n";
        std::cout << "Generating failed\n";
        std::cout << "-------------------------\n";
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Generated: " << generated << "\n";
        std::cout << "-------------------------\n";
    }
    return generated;
}

std::string unescape(std::string input)
{
    namespace qi = boost::spirit::qi;

    typedef std::string::const_iterator iterator_type;

    std::string parsed;

    std::string str("'''string\\x20xto\\x20xunescape\\x3ax\\x20x\\n\\r\\t\\\"\\'\\x41x\\x64xa'''");
    char const* quote = "'''";

    iterator_type iter = str.begin();
    iterator_type end = str.end();

    unescaped_string<iterator_type> p;
    if (!qi::parse(iter, end, p(quote), parsed))
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsing failed\n";
        std::cout << "-------------------------\n";
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Parsed: " << parsed << "\n";
        std::cout << "-------------------------\n";
    }

    return parsed;
}
