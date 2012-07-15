#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/karma.hpp>

#include <iostream>
#include <string>
#include <complex>
using namespace std;

#include "ActivityLogLine.hpp"

using namespace Iocaste::Debugger;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

BOOST_FUSION_ADAPT_STRUCT(
    ActivityLogLine,
    (std::string, label)
    (std::string, content)
)

namespace Iocaste {
    namespace Debugger {

template <typename Iterator>
struct ActivityLogParser : qi::grammar<Iterator, ActivityLogLine()>
{
    ActivityLogParser() : ActivityLogParser::base_type(start)
    {
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;

        unesc_char.add("\\a", '\a')("\\b", '\b')("\\f", '\f')("\\n", '\n')
                      ("\\r", '\r')("\\t", '\t')("\\v", '\v')("\\\\", '\\')
                      ("\\\'", '\'')("\\\"", '\"')("\\0", '\0')("\\z", 26)
            ;

        unesc_str = *(unesc_char | qi::alnum | "\\x" >> qi::hex >> ";");

        label %=  +qi::alnum;
        content %= unesc_str;
        start %= label >> ": " >> content;
    }

    qi::rule<Iterator, std::string()> label;
    qi::rule<Iterator, std::string()> content;
    qi::rule<Iterator, ActivityLogLine()> start;
    qi::rule<Iterator, std::string()> unesc_str;
    qi::symbols<char const, char const> unesc_char;
};


bool ActivityLogLine::Parse(std::string str)
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef ActivityLogParser<iterator_type> ActivityLogParser;

    ActivityLogParser g; // Our grammar

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    bool success = parse(iter, end, g, *this);

    if (!success)
    {
        std::cerr << "Failed to parse" << std::endl;
        return false;
    }
    else
    {
        if (iter != end)
        {
            std::cerr << "Not all of the line was parsed: " << std::string(iter, end) << std::endl;
            return false;
        }
        else
        {
            return true;
        }
    }
}

namespace karma = boost::spirit::karma;

template <typename OutputIterator>
struct ActivityLogWriter
  : karma::grammar<OutputIterator, ActivityLogLine()>
{
    ActivityLogWriter()
      : ActivityLogWriter::base_type(start)
    {
        esc_char.add('\a', "\\a")('\b', "\\b")('\f', "\\f")('\n', "\\n")
                    ('\r', "\\r")('\t', "\\t")('\v', "\\v")('\\', "\\\\")
                    ('\'', "\\\'")('\"', "\\\"")('\0', "\\0")(26, "\\z")
            ;

        esc_str = *(esc_char | karma::print | "\\x" << karma::hex << ";");

        label %= +karma::print;
        content %= esc_str;
        start %= label << ": " << content;
    }

    karma::rule<OutputIterator, std::string()> label;
    karma::rule<OutputIterator, std::string()> content;
    karma::rule<OutputIterator, ActivityLogLine()> start;
    karma::rule<OutputIterator, std::string()> esc_str;
    karma::symbols<char, char const*> esc_char;
};

bool ActivityLogLine::Write(std::string& generated) const
{
    namespace karma = boost::spirit::karma;

    typedef std::back_insert_iterator<std::string> sink_type;

    sink_type sink(generated);

    ActivityLogWriter<sink_type> g;
    if (!karma::generate(sink, g, *this))
    {
        std::cout << "-------------------------\n";
        std::cout << "Generating failed\n";
        std::cout << "-------------------------\n";
        return false;
    }
    else
    {
        std::cout << "-------------------------\n";
        std::cout << "Generated: " << generated << "\n";
        std::cout << "-------------------------\n";
        return true;
    }
}

    }
}

