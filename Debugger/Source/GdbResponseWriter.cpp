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
  : karma::grammar<OutputIterator, vector<GdbResponseType>()>
{
    GdbResponseWriteGrammar()
      : GdbResponseWriteGrammar::base_type(start)
    {
        banner = karma::lit("GNU gdb ") << karma::string << karma::string;
        dummy %= karma::string;
        reading_libs = karma::lit("Reading symbols for shared libraries ") << karma::string << " done";
        typedef karma::uint_generator<unsigned long long, 16> address;
        breakpoint_set = karma::lit("Breakpoint ") << karma::int_ << " at 0x" << address() << ": file " << karma::string << ", line " << karma::int_ << ".";
        empty = karma::lit("") << -dummy;

        //\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7:62:beg:0x100000e46
        cursor_pos = karma::lit("\x1A\x1A") << karma::string << ":" << karma::int_ << ":" << karma::int_ << ":" << karma::string << ":0x" << address();

        // Breakpoint 1, main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        breakpoint_hit = karma::lit("Breakpoint ") << karma::int_ << ", " << karma::string << " (" << karma::string << ") at " << karma::string << ":" << karma::int_;

        // No locals.
        // No symbol table info available.
        locals_info = karma::string;

        response_item = (banner | reading_libs | breakpoint_set | breakpoint_hit | cursor_pos | locals_info | empty) << "\n";
        start = *response_item;
    }

    karma::rule<OutputIterator, string()> dummy;
    karma::rule<OutputIterator, GdbResponses::Banner()> banner;
    karma::rule<OutputIterator, GdbResponses::ReadingLibs()> reading_libs;
    karma::rule<OutputIterator, GdbResponses::BreakpointSet()> breakpoint_set;
    karma::rule<OutputIterator, GdbResponses::BreakpointHit()> breakpoint_hit;
    karma::rule<OutputIterator, GdbResponses::CursorPos()> cursor_pos;
    karma::rule<OutputIterator, GdbResponses::LocalsInfo()> locals_info;
    karma::rule<OutputIterator, GdbResponses::Empty()> empty;
    karma::rule<OutputIterator, GdbResponseType()> response_item;
    karma::rule<OutputIterator, vector<GdbResponseType>()> start;
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
        cerr << "banner is version->" << t.version << "< message->" << t.msg << "<" << endl;
    }

    void operator()(const ReadingLibs& t) const
    {
        cerr << "reading libs is (no members)" << endl;
    }

    void operator()(const LocalsInfo& t) const
    {
        cerr << "locals info is " << t.msg << endl;
    }

    void operator()(const BreakpointSet& t) const
    {
        cerr << "breakpoint set is " << t.breakpoint_number << " " << t.address << " "
        << t.file_name << " " << t.line_number << endl;
    }

    void operator()(const CursorPos& t) const
    {
        cerr << "cursor pos is"
        << " " << t.file_name
        << " " << t.line_number
        << " " << t.char_number
        << " " << t.address
        << " " << t.unknown
        << endl;
    }

    void operator()(const BreakpointHit& t) const
    {
        cerr << "breakpoint hit is"
        << " " << t.breakpoint_number
        << " " << t.function
        << " " << t.args
        << " " << t.file_name
        << " " << t.line_number
        << endl;
    }

    void operator()(const Empty& t) const
    {
        cerr << "empty is (no members)" << endl;
    }
};

string GdbResponseWriter::Write(vector<GdbResponseType> const& response) const
{
    namespace karma = boost::spirit::karma;
    typedef std::back_insert_iterator<std::string> sink_type;

    // For debugging
    for (auto element : response)
        boost::apply_visitor(GdbResponsePrinter(), element);

    std::string result;
    sink_type sink(result);

    GdbResponseWriteGrammar<sink_type> g;

    if(!karma::generate(sink, g, response))
        throw boost::enable_current_exception(GeneratorException("Error writing user response."));

    return result;
}


GdbResponseWriter::GdbResponseWriter(AbstractOutput<StringWithPrompt>& sink_)
    : sink(sink_) {}

void GdbResponseWriter::WriteData(GdbResponse const& input)
{
    string result = Write(input.values);
    cerr << "Wrote: " << result << endl;
    sink.WriteData({result, input.prompt});
}
