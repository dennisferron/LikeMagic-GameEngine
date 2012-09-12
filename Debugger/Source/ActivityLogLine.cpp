
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

#include "ActivityLogLine.hpp"
#include "Exception.hpp"
#include "StringUnescapeParser.hpp"
#include "StringEscapeWriter.hpp"

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
        label %=  +qi::alnum;
        content %= unesc_grammar;
        start %= label >> ":" >> (" " >> content | qi::eoi);
    }

    qi::rule<Iterator, std::string()> label;
    qi::rule<Iterator, std::string()> content;
    qi::rule<Iterator, ActivityLogLine()> start;
    StringUnescapeParser<Iterator> unesc_grammar;
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
        ss << "ActivityLogLine failed to parse activity log line:  ->" << str << "<-" << std::endl;
        raiseError(ParseException(ss.str()));
    }
    else
    {
        if (iter != end)
        {
            stringstream ss;
            ss << "Not all of the line was parsed: " << std::string(iter, end) << std::endl;
            raiseError(ParseException(ss.str()));
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
        label %= +karma::print;
        content %= esc_grammar;
        start %= label << ": " << content;
    }

    karma::rule<OutputIterator, std::string()> label;
    karma::rule<OutputIterator, std::string()> content;
    karma::rule<OutputIterator, ActivityLogLine()> start;
    StringEscapeWriter<OutputIterator> esc_grammar;
};

void ActivityLogLine::Write(std::string& generated) const
{
    namespace karma = boost::spirit::karma;

    typedef std::back_insert_iterator<std::string> sink_type;

    sink_type sink(generated);

    ActivityLogWriter<sink_type> g;

    if(!karma::generate(sink, g, *this))
        raiseError(GeneratorException("Error writing activity log line."));
}

    }
}

