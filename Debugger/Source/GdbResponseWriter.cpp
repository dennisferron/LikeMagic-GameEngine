#include "GdbResponseWriter.hpp"
#include "Exception.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/spirit/include/karma.hpp>
using namespace Iocaste::Debugger;

#include <string>
using namespace std;

#include "GdbResponseFusion.hpp"
using namespace Iocaste::Debugger::GdbResponses;

namespace karma = boost::spirit::karma;

template <typename OutputIterator>
struct GdbResponseWriteGrammar
  : karma::grammar<OutputIterator, GdbResponse()>
{
    GdbResponseWriteGrammar()
      : GdbResponseWriteGrammar::base_type(start)
    {
        banner = karma::lit("GNU gdb ") << karma::string << " " << karma::string;
        dummy %= karma::string;
        reading_libs = karma::lit("Reading symbols for shared libraries") << karma::lit(" .... ") << karma::lit("done") << -dummy;
        empty = karma::lit("") << -dummy;
        start = banner | reading_libs | empty;
    }

    karma::rule<OutputIterator, string()> dummy;
    karma::rule<OutputIterator, GdbResponses::Banner()> banner;
    karma::rule<OutputIterator, GdbResponses::ReadingLibs()> reading_libs;
    karma::rule<OutputIterator, GdbResponses::Empty()> empty;
    karma::rule<OutputIterator, GdbResponse()> start;
};

struct GdbResponsePrinter : boost::static_visitor<>
{
    template <typename T>
    void operator()(const T& t) const
    {
        static_assert(sizeof(T) && false, "No debug printer defined for type T");
    }

    void operator()(const Banner& t) const
    {
        cerr << "banner is " << t.version << " " << t.msg << endl;
    }

    void operator()(const ReadingLibs& t) const
    {
        cerr << "reading libs is (no members)" << endl;
    }

    void operator()(const Empty& t) const
    {
        cerr << "empty is (no members)" << endl;
    }
};

string GdbResponseWriter::Write(GdbResponse const& response) const
{
    namespace karma = boost::spirit::karma;
    typedef std::back_insert_iterator<std::string> sink_type;

    // For debugging
    boost::apply_visitor(GdbResponsePrinter(), response);

    std::string result;
    sink_type sink(result);

    GdbResponseWriteGrammar<sink_type> g;

    if(!karma::generate(sink, g, response))
        throw boost::enable_current_exception(GeneratorException("Error writing user response."));

    return result;
}


GdbResponseWriter::GdbResponseWriter(AbstractOutput<std::string>& sink_)
    : sink(sink_) {}

void GdbResponseWriter::WriteData(GdbResponse const& input)
{
    string result = Write(input);
    cerr << "Wrote: " << result << endl;
    sink.WriteData(result);
}
