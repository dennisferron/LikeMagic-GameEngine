#include "GdbResponseParser.hpp"
using namespace Iocaste::Debugger;

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/spirit/include/qi.hpp>
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

#include "GdbResponseFusion.hpp"


// Uncomment to pass otherwise unknown commands un-parsed
//#define PARSE_RAW_STRING

namespace Iocaste {
    namespace Debugger {

template <typename Iterator>
struct GdbResponseParseGrammar : qi::grammar<Iterator, vector<GdbResponseType>(), ascii::space_type>
{
    GdbResponseParseGrammar() : GdbResponseParseGrammar::base_type(start)
    {
        raw_str = +qi::print;
        ident = +(qi::alpha | qi::char_('-'));
        file_name = +(qi::print -  qi::char_(':') - qi::char_(','));
        device_name = +(qi::print); // for tty
        value = +qi::char_;
        dummy = +qi::char_('\xFF');
        version_number = +(qi::digit | qi::char_('.') | qi::char_('-'));
        banner = qi::lit("GNU") >> qi::lit("gdb") >> version_number >> value;
        reading_libs = qi::lit("Reading symbols for shared libraries") >> *(qi::char_('.') | qi::char_('+')) >> "done";
        typedef qi::uint_parser<unsigned long long, 16, 1, 9> address;
        breakpoint_set = qi::lit("Breakpoint") >> qi::int_ >> "at 0x" >> address() >> ": file" >> file_name >> "," >> "line" >> qi::int_ >> ".";

        //\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7:62:beg:0x100000e46
        cursor_pos = qi::lit("\x1A\x1A") >> file_name >> ":" >> qi::int_ >> ":" >> qi::int_ >> ":" >> *qi::alpha >> ":0x" >> address();

        empty = -dummy;
        response_item = banner | reading_libs | breakpoint_set | cursor_pos | empty;
        start = response_item >> *(qi::lit("\n") >> response_item) >> qi::eoi;
    }

    qi::rule<Iterator, std::string()> raw_str;
    qi::rule<Iterator, std::string()> ident;
    qi::rule<Iterator, std::string()> value;
    qi::rule<Iterator, std::string()> dummy;
    qi::rule<Iterator, std::string()> file_name;
    qi::rule<Iterator, std::string()> device_name;
    qi::rule<Iterator, std::string()> version_number;
    qi::rule<Iterator, GdbResponses::Banner(), ascii::space_type> banner;
    qi::rule<Iterator, GdbResponses::ReadingLibs(), ascii::space_type> reading_libs;
    qi::rule<Iterator, GdbResponses::BreakpointSet(), ascii::space_type> breakpoint_set;
    qi::rule<Iterator, GdbResponses::CursorPos()> cursor_pos;
    qi::rule<Iterator, GdbResponses::Empty(), ascii::space_type> empty;
    qi::rule<Iterator, GdbResponseType(), ascii::space_type> response_item;
    qi::rule<Iterator, vector<GdbResponseType>(), ascii::space_type> start;
};


vector<GdbResponseType> GdbResponseParser::Parse(string const& input) const
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef GdbResponseParseGrammar<iterator_type> GdbResponseGrammar;

    GdbResponseGrammar g; // Our grammar

    std::string::const_iterator iter = input.begin();
    std::string::const_iterator end = input.end();
    vector<GdbResponseType> result;
    bool success = phrase_parse(iter, end, g, space, result);

    if (!success)
    {
        stringstream ss;
        ss << "Failed to parse: " << input << std::endl;
        cerr << endl << ss.str() << endl;
        throw boost::enable_current_exception(ParseException(ss.str()));
    }
    else
    {
        if (iter != end)
        {
            stringstream ss;
            ss << "Not all of the line was parsed: " << std::string(iter, end) << std::endl;
            cerr << endl << ss.str() << endl;
            throw boost::enable_current_exception(ParseException(ss.str()));
        }
    }

    return result;
}


GdbResponseParser::GdbResponseParser(AbstractOutput<GdbResponse>& sink_)
    : sink(sink_)
{
}

void GdbResponseParser::WriteData(StringWithPrompt const& input)
{
    GdbResponse cmd = { Parse(input.content), input.prompt };
    sink.WriteData(cmd);
}

    }
}
