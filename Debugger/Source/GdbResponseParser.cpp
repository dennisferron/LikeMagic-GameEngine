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
struct GdbResponseParseGrammar : qi::grammar<Iterator, GdbResponse(), ascii::space_type>
{
    GdbResponseParseGrammar() : GdbResponseParseGrammar::base_type(start)
    {
        raw_str = +qi::print;
        ident = +(qi::alpha | qi::char_('-'));
        file_name = +(qi::print -  qi::char_(':'));
        device_name = +(qi::print); // for tty
        value = +qi::char_;
        dummy = *qi::char_('\xFF');
        version_number = +(qi::digit | qi::char_('.'));
        banner = qi::lit("GNU") >> qi::lit("gdb") >> version_number >> +qi::char_;
        reading_libs = qi::lit("Reading symbols for shared libraries .... done") >> -dummy;
        empty = !qi::char_ >> -dummy;
        start = (banner | empty) >> -qi::lit("\n") >> qi::lit(">>>>>>cb_gdb:")
        #ifdef PARSE_RAW_STRING
            | raw_str
        #endif
        ;
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
    qi::rule<Iterator, GdbResponses::Empty(), ascii::space_type> empty;
    qi::rule<Iterator, GdbResponse(), ascii::space_type> start;
};


GdbResponse GdbResponseParser::Parse(std::string str) const
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef GdbResponseParseGrammar<iterator_type> GdbResponseGrammar;

    GdbResponseGrammar g; // Our grammar

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    GdbResponse result;
    bool success = phrase_parse(iter, end, g, space, result);

    if (!success)
    {
        stringstream ss;
        ss << "Failed to parse: " << str << std::endl;
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

void GdbResponseParser::WriteData(std::string const& input)
{
    GdbResponse cmd = Parse(input);
    sink.WriteData(cmd);
}

    }
}
