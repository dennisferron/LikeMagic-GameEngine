#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <iostream>
#include <string>
#include <complex>

#include "Parser.hpp"
using namespace Iocaste::Debugger;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

BOOST_FUSION_ADAPT_STRUCT(
    SetPrompt,
    (std::string, new_prompt)
)


BOOST_FUSION_ADAPT_STRUCT(
    SetBreakpoint,
    (std::string, file_name)
    (int, line_number)
)

namespace Iocaste {
    namespace Debugger {

template <typename Iterator>
struct SetPromptParser : qi::grammar<Iterator, SetPrompt(), ascii::space_type>
{
    SetPromptParser() : SetPromptParser::base_type(start)
    {
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;

        prompt %= lexeme[ +char_ ];

        start %=
            lit("set")
            >> "prompt"
            >>  prompt
            ;
    }

    qi::rule<Iterator, std::string(), ascii::space_type> prompt;
    qi::rule<Iterator, SetPrompt(), ascii::space_type> start;
};


template <typename Iterator>
struct SetBreakpointParser : qi::grammar<Iterator, SetBreakpoint(), ascii::space_type>
{
    SetBreakpointParser() : SetBreakpointParser::base_type(start)
    {
        using qi::int_;
        using qi::lit;
        using qi::double_;
        using qi::lexeme;
        using ascii::char_;

        file_name %= lexeme[ +(char_ - ':') ];
        //file_name %= lexeme['"' >> +(char_ - '"' - ) >> '"'];
        //line_number %= lexeme[ +int_ ];

        start %=
            lit("break")
            >> "\""
            >> file_name
            >> ":"
            >>  int_
            >> "\""
            ;
    }

    qi::rule<Iterator, std::string(), ascii::space_type> file_name;
    //qi::rule<Iterator, int, ascii::space_type> line_number;
    qi::rule<Iterator, SetBreakpoint(), ascii::space_type> start;
};


bool Parse(std::string str, SetPrompt& prompt)
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef SetPromptParser<iterator_type> SetPromptParser;

    SetPromptParser g; // Our grammar

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    bool success = phrase_parse(iter, end, g, space, prompt);

    if (!success)
    {
        std::cerr << "Failed to parse set prompt." << std::endl;
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


bool Parse(std::string str, SetBreakpoint& breakpoint)
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef SetBreakpointParser<iterator_type> SetBreakpointParser;

    SetBreakpointParser g;

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    bool success = phrase_parse(iter, end, g, space, breakpoint);

    if (!success)
    {
        std::cerr << "Failed to parse set breakpoint." << std::endl;
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

    }
}
