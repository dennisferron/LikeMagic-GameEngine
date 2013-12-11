#include "GdbResponseParser.hpp"
using namespace IoDbg;

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <iostream>
#include <string>
#include <complex>
using namespace std;

#include <boost/algorithm/string.hpp>
#include "boost/algorithm/string/predicate.hpp"

#include <boost/spirit/home/phoenix/bind/bind_member_variable.hpp>
#include <boost/spirit/home/phoenix/scope/let.hpp>
#include <boost/spirit/home/phoenix/scope/local_variable.hpp>
#include <boost/spirit/home/phoenix/statement/if.hpp>
using namespace boost::phoenix::local_names;
namespace phx = boost::phoenix;

#include "Exception.hpp"
#include "ParseGrammars.hpp"

using namespace IoDbg;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

#include "GdbResponseFusion.hpp"

using namespace IoDbg::Rules;

namespace IoDbg {

GdbResponseParser::~GdbResponseParser()
{
}

vector<GdbResponseType> GdbResponseParser::Parse(string const& input) const
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;

    iterator_type banner_iter = input.begin();
    iterator_type banner_end = input.end();
    vector<GdbResponseType> result;

    // The banner doesn't conform to the pattern of the other GdbResponses.
    // Rather than twist the grammar to handle it I just handle it with another parser.
    unique_ptr<qi::grammar<iterator_type, Rules::Banner()>> g_banner(gdb_banner_parse_grammar()); // Banner grammar
    Rules::Banner banner;

    bool is_banner = false;

    try
    {
        is_banner = parse(banner_iter, banner_end, *g_banner, banner);
    }
    catch (boost::spirit::qi::expectation_failure<iterator_type> const& exc)
    {
        cerr << "While checking for gdb banner, got parse error: " << exc.what() << " at ->" << std::string(exc.first, exc.last) << "<-" << endl;
        logError(exc);
        result.push_back(GdbUnactionable {Rules::RawStr {input}});
        return result;
    }

    if (is_banner)
    {
        while (banner.msg.size() > 0 && *banner.msg.rbegin() == '\n')
            banner.msg.resize(banner.msg.size()-1);

        result.push_back(GdbUnactionable {banner});
        return result;
    }
    else
    {
        // When the grammar fails to match I want to know which line failed.
        // I found it easiest to just handle each line individually.
        vector<string> lines;
        boost::split(lines, input, boost::is_any_of("\n"));

        // Grrr, boost split adds a suprious empty entry at the end for the last newline.
        // It also writes one vector entry for an empty input string instead of returning zero elements.
        if ( (*(lines.end()-1)).size() == 0)
            lines.erase(lines.end()-1);

        for (string line : lines)
        {
            if (line.size() == 0)
            {
                result.push_back(GdbActionable {Rules::Empty()});
            }
            else
            {
                unique_ptr<
                    qi::grammar<iterator_type, GdbResponseType()>
                > g(response_parse_grammar(use_alt_parser)); // Our grammar
                iterator_type iter = line.begin();
                iterator_type end = line.end();

                try
                {
                    GdbResponseType line_item;
                    bool success = parse(iter, end, *g, line_item);

                    if (!success)
                    {
                        stringstream ss;
                        ss << "GdbResponse failed to parse ->" << line << "<- in string ->" << input << "<-" << std::endl;
                        cerr << endl << ss.str() << endl;
                        logError(ParseException(ss.str()));
                        result.push_back(GdbUnactionable { Rules::RawStr {line}});
                    }
                    else if (iter != end)
                    {
                        stringstream ss;
                        ss << "Not all of the line was parsed. Part not parsed: ->" << std::string(iter, end) << "<-" << std::endl
                            << "from input ->" << line << "<-" << endl;
                        cerr << endl << ss.str() << endl;
                        logError(ParseException(ss.str()));
                        result.push_back(GdbUnactionable { Rules::RawStr {line}});
                    }
                    else
                    {
                        result.push_back(line_item);
                    }
                }
                catch (boost::spirit::qi::expectation_failure<iterator_type> const& exc)
                {
                    stringstream ss;
                    ss << "While parsing ->" << line << "<- in string ->" << input << "<- got expectation failure: " << exc.what() << " at " << std::string(exc.first, exc.last) << endl;
                    logError(exc);
                    result.push_back(GdbUnactionable { Rules::RawStr {line} });
                }
            }
        }
    }

    return result;
}


GdbResponseParser::GdbResponseParser(AbstractOutput<GdbResponse>& sink_)
    : sink(sink_), use_alt_parser(false)
{
}

void GdbResponseParser::expectAltInput()
{
    use_alt_parser = true;
}

void GdbResponseParser::WriteData(StringWithPrompt const& input)
{
    GdbResponse response = { Parse(input.content), input.prompt };

    if (use_alt_parser)
        use_alt_parser = false;

    sink.WriteData(response);
}

}
