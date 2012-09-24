
#include "ParseGrammars.hpp"
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

#include <boost/algorithm/string.hpp>
#include "boost/algorithm/string/predicate.hpp"

#include <boost/spirit/home/phoenix/bind/bind_member_variable.hpp>
#include <boost/spirit/home/phoenix/scope/let.hpp>
#include <boost/spirit/home/phoenix/scope/local_variable.hpp>
#include <boost/spirit/home/phoenix/statement/if.hpp>
using namespace boost::phoenix::local_names;
namespace phx = boost::phoenix;

#include "Exception.hpp"

using namespace Iocaste::Debugger;

namespace qi = boost::spirit::qi;
namespace ascii = boost::spirit::ascii;

#include "GdbResponseFusion.hpp"
#include "StringUnescapeParser.hpp"

namespace Iocaste {
    namespace Debugger {

struct GdbResponseParseGrammar : qi::grammar<std::string::const_iterator, GdbResponseType()>
{
    typedef std::string::const_iterator Iterator;

    GdbResponseParseGrammar(bool use_alt_parser) :
        GdbResponseParseGrammar::base_type(use_alt_parser? alt_start : start),
            gdb_value(gdb_value_parse_grammar())
    {
        ident = +(qi::alpha | qi::char_('-') | qi::char_('_'));

        file_name = +(qi::print -  qi::char_(':') - qi::char_(','));
        device_name = +(qi::print); // for tty
        dummy = +qi::char_('\xFF');
        function_name = +(qi::char_ - qi::char_(' '));
        gdb_function = function_name > " (" > -(function_arg % ", ") > ")";
        function_arg = ident > equals > *gdb_value;
        version_number = +(qi::digit | qi::char_('.') | qi::char_('-'));

        // Reading symbols for shared libraries .... done
        // Reading symbols from /home/dennis/code/LikeMagic-All/Iocaste/Debugger/TestProject/TestProject...done.
        reading_symbols = qi::lit("Reading ") > +qi::char_;

        program_exited = qi::lit("Program exited ") > program_exited_str;
        program_exited_str = +qi::print > qi::eoi;

        address = qi::lit("0x") > +qi::alnum;

        breakpoint_set = qi::lit("Breakpoint ") >> qi::int_ >> " at " >> address >> ": file " >> file_name >> "," >> " line " >> qi::int_ >> ".";

        breakpoint_pending = qi::lit("Breakpoint ") >> qi::int_ >> " (" >> *(qi::char_ - qi::char_(')')) >> ") pending.";

        //\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7:62:beg:0x100000e46
        cursor_pos = qi::lit("\x1A\x1A") >> file_name >> ":" >> qi::int_ >> ":" >> qi::int_ >> ":" >> *qi::alpha >> ":" >> address;

        // Breakpoint 2, io_debugger_break_here (self=0x7fff5fbffdff, locals=0x7fff5fbffdfe, m=0x7fff5fbffdfd, breakpoint_number=1,
        //      file_name=0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\", line_number=5)
        //          at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26
        // Breakpoint 1, main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        // Breakpoint 2, io_debugger_break_here (self=0x7fff5fbffdff, locals=0x7fff5fbffdfe, m=0x7fff5fbffdfd, breakpoint_number=1,
        //      file_name=0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\", line_number=5)
        //          at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26
        // Breakpoint 2, io_debugger_break_here (self=0x7fff5fbffdff, locals=0x7fff5fbffdfe, m=0x7fff5fbffdfd, breakpoint_number=1, file_name=0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\", line_number=5) at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26\n\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26:627:beg:0x100000a55\n\b>>>>>>cb_gdb:
        breakpoint_hit = qi::lit("Breakpoint ") >> qi::int_ >> ", " > gdb_function > " at " > file_name > ":" > qi::int_;

        // No locals.
        // No symbol table info available.
        no_locals_str = qi::string("No locals.") | qi::string("No arguments.") | qi::string("No symbol table info available.");
        no_locals = no_locals_str;
        locals_info = (no_locals | variable_equals);

        equals = -qi::space >> qi::char_("=") >> -qi::space;

        // self = (IoObject *) 0x7fff5fbffdff
        // locals = (IoObject *) 0x7fff5fbffdfe
        // m = (IoMessage *) 0x7fff5fbffdfd
        // breakpoint_number = 1
        // file_name = 0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\"
        // line_number = 5\n\b>>>>>>cb_gdb:
        variable_equals = ident >> equals >> -type_cast >> *gdb_value;
        type_cast = type_cast_str;
        type_cast_str = qi::char_('(') >> *(qi::char_ - qi::char_(')')) >> qi::char_(')') >> -qi::char_(' ');

        square_bracket_msg = qi::lit('[') >> *(qi::char_ - qi::char_(']')) >> qi::lit(']');


        // 0x0000000100000e20 in start ()
        address_in_function = address_in >> gdb_function;

        // #6  0xb7f42f47 in operator new () from /usr/lib/libstdc++.so.6
        // #7  0x0805bd20 in Image<Color>::fft (this=0xb467640) at ../image_processing/image.cpp:545
        // #0  main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        // #0  0x0000000100000e20 in start ()
        // -(address in) (function|?? (args)) ((at file:line)(from module))
        // #10 0x000000000050b85b in IoObject_doString (self=0x86c760, locals=0x86c760, m=0x93ed20) at /home/dennis/code/LikeMagic-All/Iocaste/iovm/source/IoObject.c:1849
        backtrace_line = qi::lit("#") > qi::int_ > +qi::space
            > -address_in
            > gdb_function
            > -from_module
            > -at_file
            > -(qi::lit(":") > qi::int_);

        address_in = address >> " in ";
        from_module = qi::lit(" from ") >> file_name;
        at_file = qi::lit(" at ") >> file_name;

        value_history = qi::lit('$') >> qi::int_ >> equals >> *gdb_value;

        // Program received signal EXC_BAD_ACCESS, Could not access memory.
        signal_received = qi::lit("Program received signal ") > +qi::char_;

        // Working directory /Users/dennisferron/code/LikeMagic-All/Iocaste.
        working_directory = qi::lit("Working directory ") > up_to_last_period > '.';
        up_to_last_period = *( qi::char_ - ( qi::lit('.')>>qi::eoi ) );

        type_equals = qi::lit("type = ") > +qi::char_;

        empty = qi::lit("") >> -*qi::char_('`') >> qi::eoi;

        output_value = *gdb_value;

        actionable =  breakpoint_set | breakpoint_pending | cursor_pos | breakpoint_hit | locals_info | address_in_function
                | backtrace_line | value_history | program_exited | working_directory | type_equals | empty;

        unactionable = reading_symbols | square_bracket_msg | signal_received;

        context_sens = output_value;

        start = actionable | unactionable;
        alt_start = context_sens;
    }

    unique_ptr<qi::grammar<Iterator, SharedTypes::GdbValue()>> gdb_value;
    qi::rule<Iterator, std::string()> ident;
    qi::rule<Iterator, std::string()> value;
    qi::rule<Iterator, std::string()> dummy;
    qi::rule<Iterator, std::string()> file_name;
    qi::rule<Iterator, std::string()> function_name;
    qi::rule<Iterator, std::string()> device_name;
    qi::rule<Iterator, std::string()> version_number;
    qi::rule<Iterator, std::string()> equals;
    qi::rule<Iterator, std::string()> no_locals_str;
    qi::rule<Iterator, std::string()> type_cast_str;
    qi::rule<Iterator, std::string()> program_exited_str;
    qi::rule<Iterator, std::string()> up_to_last_period;
    qi::rule<Iterator, SharedTypes::AtFile()> at_file;
    qi::rule<Iterator, SharedTypes::FromModule()> from_module;
    qi::rule<Iterator, SharedTypes::GdbAddress()> address;
    qi::rule<Iterator, SharedTypes::AddressIn()> address_in;
    qi::rule<Iterator, SharedTypes::NoLocals()> no_locals;
    qi::rule<Iterator, SharedTypes::TypeCast()> type_cast;
    qi::rule<Iterator, SharedTypes::VariableEquals()> variable_equals;
    qi::rule<Iterator, SharedTypes::GdbResponseFunctionArg()> function_arg;
    qi::rule<Iterator, SharedTypes::GdbResponseFunction()> gdb_function;
    qi::rule<Iterator, GdbResponses::SquareBracketMsg()> square_bracket_msg;
    qi::rule<Iterator, GdbResponses::SignalReceived()> signal_received;
    qi::rule<Iterator, GdbResponses::ProgramExited()> program_exited;
    qi::rule<Iterator, GdbResponses::ValueHistory()> value_history;
    qi::rule<Iterator, GdbResponses::LocalsInfo()> locals_info;
    qi::rule<Iterator, GdbResponses::ReadingSymbols()> reading_symbols;
    qi::rule<Iterator, GdbResponses::BreakpointSet()> breakpoint_set;
    qi::rule<Iterator, GdbResponses::BreakpointPending()> breakpoint_pending;
    qi::rule<Iterator, GdbResponses::BreakpointHit()> breakpoint_hit;
    qi::rule<Iterator, GdbResponses::BacktraceLine()> backtrace_line;
    qi::rule<Iterator, GdbResponses::WorkingDirectory()> working_directory;
    qi::rule<Iterator, GdbResponses::AddressInFunction()> address_in_function;
    qi::rule<Iterator, GdbResponses::CursorPos()> cursor_pos;
    qi::rule<Iterator, GdbResponses::TypeEquals()> type_equals;
    qi::rule<Iterator, GdbResponses::OutputValue()> output_value;
    qi::rule<Iterator, GdbResponses::Empty()> empty;
    qi::rule<Iterator, GdbActionable()> actionable;
    qi::rule<Iterator, GdbUnactionable()> unactionable;
    qi::rule<Iterator, GdbContextSensitive()> context_sens;
    qi::rule<Iterator, GdbResponseType()> start;
    qi::rule<Iterator, GdbResponseType()> alt_start;
};

boost::spirit::qi::grammar<std::string::const_iterator, GdbResponseType()>* response_parse_grammar(bool use_alt_parser)
{
    return new GdbResponseParseGrammar(use_alt_parser);
}

    }
}

