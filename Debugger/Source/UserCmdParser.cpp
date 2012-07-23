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
    UserSetOption,
    (std::string, name)
    (std::string, value)
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

        unesc_str = *(unesc_char | qi::print | "\\x" >> qi::hex >> ";");

        label %=  +qi::alnum;
        content %= unesc_str;
        start %= label >> ": " >> content;
    }

    qi::rule<Iterator, std::string()> label;
    qi::rule<Iterator, std::string()> content;
    qi::rule<Iterator, UserCmd()> start;
    qi::rule<Iterator, std::string()> unesc_str;
    qi::symbols<char const, char const> unesc_char;
};


void ActivityLogLine::Parse(std::string str)
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

void ActivityLogLine::Write(std::string& generated) const
{
    namespace karma = boost::spirit::karma;

    typedef std::back_insert_iterator<std::string> sink_type;

    sink_type sink(generated);

    ActivityLogWriter<sink_type> g;

    if(!karma::generate(sink, g, *this))
        throw boost::enable_current_exception(GeneratorException("Error writing activity log line."));
}


UserCmdParser::UserCmdParser(AbstractOutput<UserCmd>& sink_)
    : sink(sink_)
{
}

void UserCmdParser::WriteData(std::string const& input)
{
    UserCmd cmd;
    cmd.raw_string = input;
    sink.WriteData(cmd);
}


    }
}
