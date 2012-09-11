#include "GdbResponseWriter.hpp"
#include "Exception.hpp"
#include "SharedTypesPrinter.hpp"

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

        reading_symbols = karma::lit("Reading ") << karma::string;

        function_name = karma::string;
        ident = karma::string;
        address = karma::lit("0x") << karma::string;
        file_name = karma::string;
        equals = karma::string;

        gdb_function = function_name << " (" << -(function_arg % ", ") << ")";
        function_arg = ident << equals << gdb_value;

        gdb_struct = karma::lit("{") << karma::string << "}";

        square_bracket_msg = karma::lit("[") << karma::string << "]";

        breakpoint_set = karma::lit("Breakpoint ") << karma::int_ << " at " << address << ": file " << file_name << ", line " << karma::int_ << ".";
        empty = karma::lit("") << -dummy;

        raw_str = karma::string;

        program_exited = karma::lit("Program exited ") << karma::string;

        //\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7:62:beg:0x100000e46
        cursor_pos = karma::lit("\x1A\x1A") << file_name << ":" << karma::int_ << ":" << karma::int_ << ":" << karma::string << ":" << address;

        // Breakpoint 1, main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        breakpoint_hit = karma::lit("Breakpoint ") << karma::int_ << ", " << gdb_function << " at " << file_name << ":" << karma::int_;

        // #0  0x0000000100000e20 in start ()
        // #0  main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        //backtrace_line = karma::int_ << -karma::string << karma::string << karma::string << -karma::string << -karma::string << -karma::int_;
        backtrace_line = karma::lit("#") << karma::int_ << karma::lit("  ")
            << -address_in
            << gdb_function
            << -from_module
            << -at_file
            << -(karma::lit(":") << karma::int_);

        address_in = address << karma::lit(" in ");
        from_module = karma::lit(" from ") << file_name;
        at_file = karma::lit(" at ") << file_name;

        // No locals.
        // No symbol table info available.
        locals_info = karma::lit("") << (no_locals | variable_equals);
        no_locals_str = karma::string;
        no_locals = no_locals_str;
        variable_equals = ident << equals << -type_cast << gdb_value;
        type_cast = karma::string;
        gdb_value = (address | karma::int_ | quoted_string | gdb_struct)
            << -value_as_string;
        value_as_string = karma::lit(" ") << quoted_string;

        value_history = karma::lit('$') << karma::int_ << equals << gdb_value;

        // 0x0000000100000e20 in start ()
        address_in_function = address_in << gdb_function;

        quoted_string = karma::lit("\"") << karma::string << "\"";

        test_str1 = karma::string;
        test_str2 = karma::string;

        response_item = (locals_info | test_str1 | backtrace_line | banner | reading_symbols | breakpoint_set | breakpoint_hit | cursor_pos | address_in_function | program_exited
                         | square_bracket_msg | raw_str | empty) << "\n";
        start = *response_item;
    }

    karma::rule<OutputIterator, string()> dummy;
    karma::rule<OutputIterator, string()> quoted_string;
    karma::rule<OutputIterator, string()> function_name;
    karma::rule<OutputIterator, string()> ident;
    karma::rule<OutputIterator, string()> equals;
    karma::rule<OutputIterator, string()> no_locals_str;
    karma::rule<OutputIterator, SharedTypes::NoLocals()> no_locals;
    karma::rule<OutputIterator, SharedTypes::GdbAddress()> address;
    karma::rule<OutputIterator, SharedTypes::GdbStruct()> gdb_struct;
    karma::rule<OutputIterator, string()> file_name;
    karma::rule<OutputIterator, SharedTypes::AddressIn()> address_in;
    karma::rule<OutputIterator, SharedTypes::FromModule()> from_module;
    karma::rule<OutputIterator, SharedTypes::AtFile()> at_file;
    karma::rule<OutputIterator, SharedTypes::ValueAsString()> value_as_string;
    karma::rule<OutputIterator, SharedTypes::TypeCast()> type_cast;
    karma::rule<OutputIterator, SharedTypes::GdbValue()> gdb_value;
    karma::rule<OutputIterator, SharedTypes::VariableEquals()> variable_equals;
    karma::rule<OutputIterator, SharedTypes::GdbResponseFunction()> gdb_function;
    karma::rule<OutputIterator, SharedTypes::GdbResponseFunctionArg()> function_arg;
    karma::rule<OutputIterator, GdbResponses::ProgramExited()> program_exited;
    karma::rule<OutputIterator, GdbResponses::Banner()> banner;
    karma::rule<OutputIterator, GdbResponses::ValueHistory()> value_history;
    karma::rule<OutputIterator, GdbResponses::ReadingSymbols()> reading_symbols;
    karma::rule<OutputIterator, GdbResponses::BreakpointSet()> breakpoint_set;
    karma::rule<OutputIterator, GdbResponses::BreakpointHit()> breakpoint_hit;
    karma::rule<OutputIterator, GdbResponses::CursorPos()> cursor_pos;
    karma::rule<OutputIterator, GdbResponses::LocalsInfo()> locals_info;
    karma::rule<OutputIterator, GdbResponses::BacktraceLine()> backtrace_line;
    karma::rule<OutputIterator, GdbResponses::AddressInFunction()> address_in_function;
    karma::rule<OutputIterator, GdbResponses::Empty()> empty;
    karma::rule<OutputIterator, GdbResponses::TestStr1()> test_str1;
    karma::rule<OutputIterator, GdbResponses::TestStr2()> test_str2;
    karma::rule<OutputIterator, GdbResponses::RawStr()> raw_str;
    karma::rule<OutputIterator, GdbResponses::SquareBracketMsg()> square_bracket_msg;
    karma::rule<OutputIterator, GdbResponseType()> response_item;
    karma::rule<OutputIterator, vector<GdbResponseType>()> start;
};

struct GdbResponsePrinter : public SharedTypesPrinter
{
    void operator()(const ProgramExited& t) const
    {
        cerr << "Program exited, how: " << t.how << endl;
    }

    void operator()(const ValueHistory& t) const
    {
        cerr << "Value history is $" << t.number << endl;
    }

    void operator()(const RawStr& t) const
    {
        cerr << "RawStr is " << t.value << endl;
    }

    void operator()(const SquareBracketMsg& t) const
    {
        cerr << "SquareBracketMsg is " << t.msg << endl;
    }

    void operator()(const UninitializedVariant& t) const
    {
        cerr << "got uninitialized variant" << endl;
        //raiseError(GeneratorException("Generator was passed uninitialized variant in GdbResponse object."));
    }

    void operator()(const TestStr1& t) const
    {
        cerr << "got test string1 ->" << t.value << "<-" << endl;
    }

    void operator()(const TestStr2& t) const
    {
        cerr << "got test string2 ->" << t.value << "<-" << endl;
    }

    void operator()(const Banner& t) const
    {
        cerr << "banner is version->" << t.version << "< message->" << t.msg << "<" << endl;
    }

    void operator()(const ReadingSymbols& t) const
    {
        cerr << "reading libs is " << t.message << endl;
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
    for (auto element : response)
        boost::apply_visitor(GdbResponsePrinter(), element);

    std::string result;
    sink_type sink(result);

    GdbResponseWriteGrammar<sink_type> g;

    if(!karma::generate(sink, g, response))
        raiseError(GeneratorException("Error writing user response."));

    return result;
}


GdbResponseWriter::GdbResponseWriter(AbstractOutput<StringWithPrompt>& sink_)
    : sink(sink_) {}

void GdbResponseWriter::WriteData(GdbResponse const& input)
{
    string result = Write(input.values);
    sink.WriteData({result, input.prompt});
}
