#include "GdbResponseWriter.hpp"
#include "Exception.hpp"
#include "SharedTypesPrinter.hpp"

#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include "WriteGrammars.hpp"

using namespace IoDbg;

#include <string>
using namespace std;

#include "StringEscapeWriter.hpp"

using namespace IoDbg::GdbResponses;

namespace IoDbg {

struct GdbResponsePrinter : public SharedTypesPrinter
{
    void operator()(const OutputValue& t) const
    {
        cerr << "OutputValue is GdbValue" << endl;
    }

    void operator()(const ProgramExited& t) const
    {
        cerr << "Program exited, how: " << t.how << endl;
    }

    void operator()(const ValueHistory& t) const
    {
        cerr << "Value history is $" << t.number << endl;
    }

    void operator()(const TypeEquals& t) const
    {
        cerr << "Type equals is " << t.type << endl;
    }

    void operator()(const RawStr& t) const
    {
        cerr << "RawStr is " << t.value << endl;
    }

    void operator()(const SquareBracketMsg& t) const
    {
        cerr << "SquareBracketMsg is " << t.msg << endl;
    }

    void operator()(const SignalReceived& t) const
    {
        cerr << "SignalReceived is " << t.msg << endl;
    }

    void operator()(const Banner& t) const
    {
        cerr << "banner is version->" << t.version << "< message->" << t.msg << "<" << endl;
    }

    void operator()(const ReadingSymbols& t) const
    {
        cerr << "reading libs is " << t.message << endl;
    }

    void operator()(const WorkingDirectory& t) const
    {
        cerr << "WorkingDirectory is " << t.directory << endl;
    }

    void operator()(const LocalsInfo& t) const
    {
        cerr << "LocalsInfo is ";
        boost::apply_visitor(SharedTypesPrinter(), t.value);
        cerr << endl;
    }

    void operator()(const BreakpointSet& t) const
    {
        cerr << "breakpoint set is "
        << t.breakpoint_number << " "
        << t.address.hex_value << " "
        << t.file_name << " "
        << t.line_number
        << endl;
    }

    void operator()(const BreakpointPending& t) const
    {
        cerr << "breakpoint pending is "
        << t.breakpoint_number << " "
        << t.func_name
        << endl;
    }

    void operator()(const CursorPos& t) const
    {
        cerr << "cursor pos is"
        << " " << t.file_name
        << " " << t.line_number
        << " " << t.char_number
        << " " << t.unknown
        << " " << t.address.hex_value
        << endl;
    }

    void operator()(const BreakpointHit& t) const
    {
        cerr << "breakpoint hit is"
        << " " << t.breakpoint_number
        << " " << t.function.name << " (";

        for (auto arg : t.function.args)
        {
            cerr << arg.name << arg.equals << "GdbValue";
            if (arg.value.value_as_string)
                cerr << " \"" << arg.value.value_as_string->text << "\"";
            cerr << ", ";
        }

        cerr << ") " << t.file_name
        << " " << t.line_number
        << endl;
    }

    template <typename T>
    void printOpt(std::string msg, boost::optional<T> value) const
    {
        if (value)
        {
            cerr << msg;
            SharedTypesPrinter()(*value);
        }
    }

    void operator()(const BacktraceLine& t) const
    {
        cerr << "backtrace line is"
        << " #" << t.backtrace_number;
        printOpt(" at addr:", t.address_in);
        cerr << " in func:" << t.function.name;
        cerr << " with args:";
        SharedTypesPrinter()(t.function.args);
        printOpt(" from module:", t.module);
        printOpt(" in file:", t.file_name);
        printOpt(" at line:", t.line_number);
        cerr << endl;
    }

    void operator()(const AddressInFunction& t) const
    {
        cerr << "address in function is"
        << " " << t.address_in.address.hex_value
        << " " << t.function.name
        << " " << t.function.args.size()
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
    //GdbResponsePrinter printer;
    //for (auto element : response)
    //    visitAll(printer, element);

    std::string result;
    sink_type sink(result);

    std::unique_ptr<
        boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, vector<GdbResponseType>()>
    > g(response_write_grammar());

    if(!karma::generate(sink, *g, response))
        raiseError(GeneratorException("Error writing user response."));

    return result;
}


GdbResponseWriter::GdbResponseWriter(AbstractOutput<StringWithPrompt>& sink_, AbstractInput<UserCmd>& fromUser_)
    : sink(sink_), fromUser(fromUser_) {}

void GdbResponseWriter::WriteData(GdbResponse const& input)
{
    if (fromUser.HasData())
        raiseError(ConcurrencyError("GdbResponseWriter detected new user command came in before response to last command could be printed."));

    if (input.prompt)
        last_prompt = *input.prompt;

    string result = Write(input.values);
    sink.WriteData({result, last_prompt});
}

}
