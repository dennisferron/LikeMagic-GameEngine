
/*=============================================================================
    Copyright (c) 2002-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A parser for arbitrary tuples. This example presents a parser
//  for an employee structure.
//
//  [ JDG May 9, 2007 ]
//
///////////////////////////////////////////////////////////////////////////////

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

// We need to tell fusion about our struct
// to make it a first-class fusion citizen. This has to
// be in global scope.
BOOST_FUSION_ADAPT_STRUCT(
    SetPrompt,
    (std::string, new_prompt)
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

    }
}
