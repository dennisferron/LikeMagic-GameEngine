#include "WriteGrammars.hpp"

#include "Exception.hpp"


#if (defined(__MINGW32__) || defined(__MINGW64__)) && (__GNUC__ == 4)
#include <stddef.h>
// workaround a mingw bug, http://sourceforge.net/tracker/index.php?func=detail&aid=2373234&group_id=2435&atid=102435
int swprintf (wchar_t *, size_t, const wchar_t *, ...);
#endif

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>
using namespace Iocaste::Debugger;

#include <string>
#include <vector>
using namespace std;

#include "WriteGrammars.hpp"

#include "GdbResponseFusion.hpp"
using namespace Iocaste::Debugger::GdbResponses;

namespace Iocaste { namespace Debugger {

namespace karma = boost::spirit::karma;
typedef std::back_insert_iterator<std::string> OutputIterator;

struct GdbResponseWriteGrammar
  : karma::grammar<OutputIterator, vector<GdbResponseType>()>
{
    GdbResponseWriteGrammar()
      : GdbResponseWriteGrammar::base_type(start), gdb_value(gdb_value_write_grammar())
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
        function_arg = ident << equals << *gdb_value;

        square_bracket_msg = karma::lit("[") << karma::string << "]";

        breakpoint_set = karma::lit("Breakpoint ") << karma::int_ << " at " << address << ": file " << file_name << ", line " << karma::int_ << ".";
        empty = karma::lit("") << -dummy;

        program_exited = karma::lit("Program exited ") << karma::string;

        //\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7:62:beg:0x100000e46
        cursor_pos = karma::lit("\x1A\x1A") << file_name << ":" << karma::int_ << ":" << karma::int_ << ":" << karma::string << ":" << address;

        // Breakpoint 1, main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        breakpoint_hit = karma::lit("Breakpoint ") << karma::int_ << ", " << gdb_function << " at " << file_name << ":" << karma::int_;

        // #0  0x0000000100000e20 in start ()
        // #0  main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        //backtrace_line = karma::int_ << -karma::string << karma::string << karma::string << -karma::string << -karma::string << -karma::int_;
        backtrace_line = karma::lit("#") << karma::int_ << karma::string
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
        variable_equals = ident << equals << -type_cast << *gdb_value;
        type_cast = karma::string;

        value_history = karma::lit('$') << karma::int_ << equals << *gdb_value;

        // 0x0000000100000e20 in start ()
        address_in_function = address_in << gdb_function;

        // Program received signal EXC_BAD_ACCESS, Could not access memory.
        signal_received = karma::lit("Program received signal ") << karma::string;

        // Working directory /Users/dennisferron/code/LikeMagic-All/Iocaste.
        working_directory = karma::lit("Working directory ") << karma::string << ".";

        type_equals = karma::lit("type = ") << karma::string;

        actionable_variant = locals_info | backtrace_line | banner | breakpoint_set | breakpoint_hit | cursor_pos | address_in_function | program_exited
                         | working_directory | type_equals | empty;
        actionable = actionable_variant << karma::lit("\n");

        unactionable_variant = banner | reading_symbols | square_bracket_msg | signal_received | raw_str;
        unactionable = unactionable_variant << karma::lit("\n");

        output_value = *gdb_value;
        context_sens_variant = output_value | output_value;
        context_sens = context_sens_variant;

        response_item = actionable | unactionable | context_sens;

        start = *response_item;
    }

    unique_ptr<
        karma::grammar<OutputIterator, SharedTypes::GdbValue()>
    > gdb_value;
    karma::rule<OutputIterator, string()> dummy;
    karma::rule<OutputIterator, string()> function_name;
    karma::rule<OutputIterator, string()> ident;
    karma::rule<OutputIterator, string()> equals;
    karma::rule<OutputIterator, string()> no_locals_str;
    karma::rule<OutputIterator, SharedTypes::NoLocals()> no_locals;
    karma::rule<OutputIterator, SharedTypes::GdbAddress()> address;
    karma::rule<OutputIterator, string()> file_name;
    karma::rule<OutputIterator, SharedTypes::AddressIn()> address_in;
    karma::rule<OutputIterator, SharedTypes::FromModule()> from_module;
    karma::rule<OutputIterator, SharedTypes::AtFile()> at_file;
    karma::rule<OutputIterator, SharedTypes::TypeCast()> type_cast;
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
    karma::rule<OutputIterator, GdbResponses::TypeEquals()> type_equals;
    karma::rule<OutputIterator, GdbResponses::RawStr()> raw_str;
    karma::rule<OutputIterator, GdbResponses::Empty()> empty;
    karma::rule<OutputIterator, GdbResponses::OutputValue()> output_value;
    karma::rule<OutputIterator, GdbResponses::SquareBracketMsg()> square_bracket_msg;
    karma::rule<OutputIterator, GdbResponses::SignalReceived()> signal_received;
    karma::rule<OutputIterator, GdbResponses::WorkingDirectory()> working_directory;
    karma::rule<OutputIterator, GdbActionableType()> actionable_variant;
    karma::rule<OutputIterator, GdbUnactionableType()> unactionable_variant;
    karma::rule<OutputIterator, GdbContextSensitiveType()> context_sens_variant;
    karma::rule<OutputIterator, GdbActionable()> actionable;
    karma::rule<OutputIterator, GdbUnactionable()> unactionable;
    karma::rule<OutputIterator, GdbContextSensitive()> context_sens;
    karma::rule<OutputIterator, GdbResponseType()> response_item;
    karma::rule<OutputIterator, vector<GdbResponseType>()> start;
};

boost::spirit::karma::grammar<std::back_insert_iterator<std::string>, vector<GdbResponseType>()>* response_write_grammar()
{
    return new GdbResponseWriteGrammar();
}

}}

