#include "UserCmdWriter.hpp"
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

#include "UserCmdFusion.hpp"
using namespace Iocaste::Debugger::UserCmds;

namespace karma = boost::spirit::karma;

template <typename OutputIterator>
struct UserCmdWriteGrammar
  : karma::grammar<OutputIterator, UserCmd()>
{
    UserCmdWriteGrammar()
      : UserCmdWriteGrammar::base_type(start)
    {
        raw_str = karma::string;
        set_option = karma::lit("set") << " " << karma::string << -(" " << karma::string) << " " << karma::string;
        show_option = karma::lit("show") << " " << karma::string << -(" " << karma::string);
        set_breakpoint = karma::lit("break") << " " << "\"" << karma::string << ":" << karma::int_ << "\"";
        source = karma::lit("source") << " " << karma::string;
        directory = karma::lit("directory") << " " << karma::string;
        tty = karma::lit("tty") << " " << karma::string;
        run = karma::lit("run") << -karma::string;
        info = karma::lit("info") << " " << karma::string;
        backtrace = karma::lit("bt") << " " << karma::int_;
        next = karma::lit("next") << -karma::string;
        step = karma::lit("step") << -karma::string;
        finish = karma::lit("finish") << -karma::string;
        quit = karma::lit("quit") << -karma::string;
        empty = karma::lit("") << -karma::string;
        start = raw_str | set_option | show_option | set_breakpoint | source | directory | tty | run | info | backtrace | next | step | finish | quit | empty;
    }

    karma::rule<OutputIterator, UserCmds::RawString()> raw_str;
    karma::rule<OutputIterator, UserCmds::SetOption()> set_option;
    karma::rule<OutputIterator, UserCmds::ShowOption()> show_option;
    karma::rule<OutputIterator, UserCmds::SetBreakpoint()> set_breakpoint;
    karma::rule<OutputIterator, UserCmds::Source()> source;
    karma::rule<OutputIterator, UserCmds::Directory()> directory;
    karma::rule<OutputIterator, UserCmds::TTY()> tty;
    karma::rule<OutputIterator, UserCmds::Run()> run;
    karma::rule<OutputIterator, UserCmds::Info()> info;
    karma::rule<OutputIterator, UserCmds::Backtrace()> backtrace;
    karma::rule<OutputIterator, UserCmds::Next()> next;
    karma::rule<OutputIterator, UserCmds::Step()> step;
    karma::rule<OutputIterator, UserCmds::Finish()> finish;
    karma::rule<OutputIterator, UserCmds::Quit()> quit;
    karma::rule<OutputIterator, UserCmds::Empty()> empty;
    karma::rule<OutputIterator, UserCmd()> start;
};

struct UserCmdPrinter : boost::static_visitor<>
{
    template <typename T>
    void operator()(const T& t) const
    {
        static_assert(sizeof(T) && false, "No debug printer defined for type T");
    }

    void operator()(const RawString& t) const
    {
        cerr << "raw string is " << t.value << endl;
    }

    void operator()(const SetOption& t) const
    {
        cerr << "set option is name '" << t.name << "'" << (t.modifier? ", mod '" + *(t.modifier) + "' " : "") << ", value '" << t.value << "'" << endl;
    }

    void operator()(const ShowOption& t) const
    {
        cerr << "show option is name '" << t.name << "'" << (t.modifier? ", mod '" + *(t.modifier) + "' " : "")<< endl;
    }

    void operator()(const SetBreakpoint& t) const
    {
        cerr << "set breakpoint is " << t.file_name << " " << t.line_number << endl;
    }

    void operator()(const Source& t) const
    {
        cerr << "source is \"" << t.file_name << "\"" << endl;
    }

    void operator()(const Directory& t) const
    {
        cerr << "directory is \"" << t.file_name << "\"" << endl;
    }

    void operator()(const TTY& t) const
    {
        cerr << "tty is \"" << t.device_name << "\"" << endl;
    }

    void operator()(const Run& t) const
    {
        cerr << "run is (no members)" << endl;
    }

    void operator()(const Info& t) const
    {
        cerr << "info is " << t.value << endl;
    }

    void operator()(const Backtrace& t) const
    {
        cerr << "bt is " << t.num_frames << endl;
    }

    void operator()(const Next& t) const
    {
        cerr << "next is (no members)" << endl;
    }

    void operator()(const Step& t) const
    {
        cerr << "step is (no members)" << endl;
    }

    void operator()(const Finish& t) const
    {
        cerr << "finish is (no members)" << endl;
    }

    void operator()(const Quit& t) const
    {
        cerr << "quit is (no members)" << endl;
    }

    void operator()(const Empty& t) const
    {
        cerr << "empty is (no members)" << endl;
    }
};

string UserCmdWriter::Write(UserCmd const& cmd) const
{
    namespace karma = boost::spirit::karma;
    typedef std::back_insert_iterator<std::string> sink_type;

    // For debugging
    boost::apply_visitor(UserCmdPrinter(), cmd);

    std::string result;
    sink_type sink(result);

    UserCmdWriteGrammar<sink_type> g;

    if(!karma::generate(sink, g, cmd))
        throw boost::enable_current_exception(GeneratorException("Error writing user cmd."));

    return result;
}


UserCmdWriter::UserCmdWriter(AbstractOutput<std::string>& sink_)
    : sink(sink_) {}

void UserCmdWriter::WriteData(UserCmd const& input)
{
    string result = Write(input);
    cerr << "Wrote: " << result << endl;
    sink.WriteData(result);
}
