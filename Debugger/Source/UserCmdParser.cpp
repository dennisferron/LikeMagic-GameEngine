#include "UserCmdParser.hpp"
using namespace Iocaste::Debugger;

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

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

#include "Exception.hpp"

using namespace Iocaste::Debugger;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::SetOption,
    (std::string, name)
    (boost::optional<std::string>, modifier)
    (std::string, value)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd::SetBreakpoint,
    (std::string, file_name)
    (int, line_number)
)

BOOST_FUSION_ADAPT_STRUCT(
    UserCmd,
    (boost::optional<std::string>, raw_string)
    (boost::optional<UserCmd::SetOption>, set_option)
    (boost::optional<UserCmd::SetBreakpoint>, set_breakpoint)
)

namespace Iocaste {
    namespace Debugger {

template <typename Iterator>
struct UserCmdParseGrammar : qi::grammar<Iterator, UserCmd(), ascii::space_type>
{
    UserCmdParseGrammar() : UserCmdParseGrammar::base_type(start)
    {
        raw_str = +qi::print;
        ident = +(qi::alpha | qi::char_('-'));
        file_name = +(qi::print -  qi::char_(':'));
        set_option = qi::lit("set") >> ident >> -ident >> +qi::print >> qi::eoi;
        set_breakpoint = qi::lit("break") >> "\"" >> file_name >> ":" >> qi::int_ >> "\"";
        start = set_option | raw_str;
    }

    qi::rule<Iterator, std::string()> raw_str;
    qi::rule<Iterator, std::string()> ident;
    qi::rule<Iterator, std::string()> file_name;
    qi::rule<Iterator, UserCmd::SetOption(), ascii::space_type> set_option;
    qi::rule<Iterator, UserCmd::SetBreakpoint(), ascii::space_type> set_breakpoint;
    qi::rule<Iterator, UserCmd(), ascii::space_type> start;
};


void UserCmd::Parse(std::string str)
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef UserCmdParseGrammar<iterator_type> UserCmdGrammar;

    UserCmdGrammar g; // Our grammar

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    bool success = phrase_parse(iter, end, g, space, *this);

    if (!success)
    {
        stringstream ss;
        ss << "Failed to parse: " << str << std::endl;
        throw boost::enable_current_exception(ParseException(ss.str()));
    }
    else
    {
        if (iter != end)
        {
            stringstream ss;
            ss << "Not all of the line was parsed: " << std::string(iter, end) << std::endl;
            throw boost::enable_current_exception(ParseException(ss.str()));
        }
    }
}


UserCmdParser::UserCmdParser(AbstractOutput<UserCmd>& sink_)
    : sink(sink_)
{
}

void UserCmdParser::WriteData(std::string const& input)
{
    UserCmd cmd;
    //cmd.raw_string = input;
    cmd.Parse(input);
    sink.WriteData(cmd);
}


    }
}
