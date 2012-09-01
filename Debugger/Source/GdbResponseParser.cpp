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


// Uncomment to pass otherwise unknown commands un-parsed
//#define PARSE_RAW_STRING

namespace Iocaste {
    namespace Debugger {

template <typename Iterator>
struct GdbResponseGrammar : qi::grammar<Iterator, GdbResponseType()>
{
    GdbResponseGrammar() : GdbResponseGrammar::base_type(start)
    {
        ident = +(qi::alpha | qi::char_('-') | qi::char_('_'));

        file_name = +(qi::print -  qi::char_(':') - qi::char_(','));
        device_name = +(qi::print); // for tty
        dummy = +qi::char_('\xFF');
        function_name = +(qi::char_ - qi::char_(' '));
        gdb_function = function_name > " (" > -(function_arg % ", ") > ")";
        function_arg = ident > equals > gdb_value;
        version_number = +(qi::digit | qi::char_('.') | qi::char_('-'));
        reading_libs = qi::lit("Reading symbols for shared libraries ") >> *(qi::char_('.') | qi::char_('+')) >> " done";

        address = qi::lit("0x") > +qi::alnum;

        breakpoint_set = qi::lit("Breakpoint ") >> qi::int_ >> " at " >> address >> ": file " >> file_name >> "," >> " line " >> qi::int_ >> ".";

        //\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7:62:beg:0x100000e46
        cursor_pos = qi::lit("\x1A\x1A") >> file_name >> ":" >> qi::int_ >> ":" >> qi::int_ >> ":" >> *qi::alpha >> ":" >> address;

        // Breakpoint 2, io_debugger_break_here (self=0x7fff5fbffdff, locals=0x7fff5fbffdfe, m=0x7fff5fbffdfd, breakpoint_number=1,
        //      file_name=0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\", line_number=5)
        //          at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26
        // Breakpoint 1, main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        // Breakpoint 2, io_debugger_break_here (self=0x7fff5fbffdff, locals=0x7fff5fbffdfe, m=0x7fff5fbffdfd, breakpoint_number=1,
        //      file_name=0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\", line_number=5)
        //          at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26

//Breakpoint 2, io_debugger_break_here (self=0x7fff5fbffdff, locals=0x7fff5fbffdfe, m=0x7fff5fbffdfd, breakpoint_number=1, file_name=0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\", line_number=5) at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26\n\z\z/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:26:627:beg:0x100000a55\n\b>>>>>>cb_gdb:
        breakpoint_hit = qi::lit("Breakpoint ") >> qi::int_ >> ", " > gdb_function > " at " > file_name > ":" > qi::int_;

        // No locals.
        // No symbol table info available.
        no_locals = qi::string("No locals.") | qi::string("No arguments.") | qi::string("No symbol table info available.");
        locals_info = (no_locals | variable_equals);

        equals = -qi::space >> qi::char_("=") >> -qi::space;

        // self = (IoObject *) 0x7fff5fbffdff
        // locals = (IoObject *) 0x7fff5fbffdfe
        // m = (IoMessage *) 0x7fff5fbffdfd
        // breakpoint_number = 1
        // file_name = 0x100001e28 \"/Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/test.io\"
        // line_number = 5\n\b>>>>>>cb_gdb:
        variable_equals = ident >> equals >> -type_cast >> gdb_value;
        type_cast = qi::char_('(') >> *(qi::char_ - qi::char_(')')) >> qi::char_(')') >> -qi::char_(' ');

        quoted_string = qi::lit('"') >> *(qi::char_ - qi::char_('"')) >> qi::lit('"');


        // 0x0000000100000e20 in start ()
        address_in_function = address_in >> gdb_function;

        // #6  0xb7f42f47 in operator new () from /usr/lib/libstdc++.so.6
        // #7  0x0805bd20 in Image<Color>::fft (this=0xb467640) at ../image_processing/image.cpp:545
        // #0  main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
        // #0  0x0000000100000e20 in start ()
        // -(address in) (function|?? (args)) ((at file:line)(from module))
        backtrace_line = qi::lit("#") >> qi::int_ >> "  "
            >> -address_in
            >> gdb_function
            >> -from_module
            >> -at_file
            >> -(qi::lit(":") >> qi::int_);

        address_in = address >> " in ";
        from_module = qi::lit(" from ") >> file_name;
        at_file = qi::lit(" at ") >> file_name;

        raw_str_value = *qi::char_;
        raw_str = raw_str_value;
        //test_str1 = qi::lit("#0  ") >> raw_str_value;

        gdb_value = (address | qi::int_ | quoted_string) >> -value_as_string;
        value_as_string = qi::lit(" ") >> quoted_string;

        value_history = qi::lit('$') >> qi::int_ >> equals >> gdb_value;

        start = reading_libs | breakpoint_set | cursor_pos | breakpoint_hit | locals_info | address_in_function | backtrace_line | value_history
        #ifdef PARSE_RAW_STRING
            | raw_str
        #endif
        ;
    }

    qi::rule<Iterator, std::string()> ident;
    qi::rule<Iterator, std::string()> value;
    qi::rule<Iterator, std::string()> dummy;
    qi::rule<Iterator, std::string()> file_name;
    qi::rule<Iterator, std::string()> function_name;
    qi::rule<Iterator, std::string()> device_name;
    qi::rule<Iterator, std::string()> version_number;
    qi::rule<Iterator, std::string()> equals;
    qi::rule<Iterator, SharedTypes::ValueAsString()> value_as_string;
    qi::rule<Iterator, SharedTypes::AtFile()> at_file;
    qi::rule<Iterator, SharedTypes::FromModule()> from_module;
    qi::rule<Iterator, SharedTypes::GdbAddress()> address;
    qi::rule<Iterator, SharedTypes::AddressIn()> address_in;
    qi::rule<Iterator, SharedTypes::NoLocals()> no_locals;
    qi::rule<Iterator, std::string()> raw_str_value;
    qi::rule<Iterator, std::string()> quoted_string;
    qi::rule<Iterator, SharedTypes::TypeCast()> type_cast;
    qi::rule<Iterator, SharedTypes::VariableEquals()> variable_equals;
    qi::rule<Iterator, SharedTypes::GdbResponseFunctionArg()> function_arg;
    qi::rule<Iterator, SharedTypes::GdbResponseFunction()> gdb_function;
    qi::rule<Iterator, SharedTypes::GdbValue()> gdb_value;
    qi::rule<Iterator, GdbResponses::ValueHistory()> value_history;
    qi::rule<Iterator, GdbResponses::TestStr1()> test_str1;
    qi::rule<Iterator, GdbResponses::LocalsInfo()> locals_info;
    qi::rule<Iterator, GdbResponses::ReadingLibs()> reading_libs;
    qi::rule<Iterator, GdbResponses::BreakpointSet()> breakpoint_set;
    qi::rule<Iterator, GdbResponses::BreakpointHit()> breakpoint_hit;
    qi::rule<Iterator, GdbResponses::BacktraceLine()> backtrace_line;
    qi::rule<Iterator, GdbResponses::AddressInFunction()> address_in_function;
    qi::rule<Iterator, GdbResponses::CursorPos()> cursor_pos;
    qi::rule<Iterator, GdbResponses::RawStr()> raw_str;
    qi::rule<Iterator, GdbResponseType()> start;
};

template <typename Iterator>
struct GdbBannerGrammar : qi::grammar<Iterator, GdbResponses::Banner()>
{
    GdbBannerGrammar() : GdbBannerGrammar::base_type(banner)
    {
        version_number = +(qi::digit | qi::char_('.') | qi::char_('-'));
        banner_line = +(qi::char_ - '\n');
        banner_message = banner_line >> qi::char_('\n') >> banner_line >> qi::char_('\n') >> banner_line >> qi::char_('\n') >> banner_line >> qi::char_('\n') >> banner_line >> qi::char_('\n') >> banner_line >> qi::char_('\n') >> banner_line;
        banner = qi::lit("GNU gdb ") >> version_number >> banner_message >> qi::lit("\n") >> qi::eoi;
    }

    qi::rule<Iterator, std::string()> version_number;
    qi::rule<Iterator, std::string()> banner_line;
    qi::rule<Iterator, std::string()> banner_message;
    qi::rule<Iterator, GdbResponses::Banner()> banner;
};


vector<GdbResponseType> GdbResponseParser::Parse(string const& input) const
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;

    iterator_type banner_iter = input.begin();
    iterator_type banner_end = input.end();
    vector<GdbResponseType> result;

    // The banner doesn't conform to the pattern of the other GdbResponses.
    // Rather than twist the grammar to handle it I just handle it with another parser.
    GdbBannerGrammar<iterator_type> g_banner; // Banner grammar
    GdbResponses::Banner banner;
    if (parse(banner_iter, banner_end, g_banner, banner))
    {
        result.push_back(banner);
        return result;
    }
    else
    {
        // When the grammar fails to match I want to know which line failed.
        // I couldn't figure out how to get spirit expectation failure to work
        // in a spirit grammar (nothing happens) so I just handle each line individually.
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
                result.push_back(GdbResponses::Empty());
            }
            else
            {
                GdbResponseGrammar<iterator_type> g; // Our grammar
                iterator_type iter = line.begin();
                iterator_type end = line.end();

                try
                {
                    GdbResponseType line_item;
                    bool success = parse(iter, end, g, line_item);

                    if (!success)
                    {
                        stringstream ss;
                        ss << "GdbResponse failed to parse ->" << line << "<- in string ->" << input << "<-" << std::endl;
                        cerr << endl << ss.str() << endl;
                        raiseError(ParseException(ss.str()));
                    }
                    else if (iter != end)
                    {
                        if (boost::get<GdbResponses::UninitializedVariant>(&line_item))
                            cerr << "Uninitialized after parse, success was " << success << " line was " << line << endl;
                        else if (auto* p = boost::get<GdbResponses::TestStr1>(&line_item))
                        {
                            cerr << "Got " << p->value << endl;
                        }

                        stringstream ss;
                        ss << "Not all of the line was parsed: " << std::string(iter, end) << std::endl;
                        cerr << endl << ss.str() << endl;
                        raiseError(ParseException(ss.str()));
                    }
                    else
                    {
                        if (boost::get<GdbResponses::UninitializedVariant>(&line_item))
                            cerr << "Uninitialized after parse, success was " << success << " line was " << line << endl;
                        else if (auto* p = boost::get<GdbResponses::TestStr1>(&line_item))
                        {
                            cerr << "Got " << p->value << endl;
                        }

                        result.push_back(line_item);
                    }
                }
                catch (boost::spirit::qi::expectation_failure<iterator_type>& exc)
                {
                    cerr << "Parse error: " << exc.what() << " at " << std::string(exc.first, exc.last) << endl;
                    raiseError(exc);
                }
            }
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
    GdbResponse response = { Parse(input.content), input.prompt };
    sink.WriteData(response);
}

    }
}
