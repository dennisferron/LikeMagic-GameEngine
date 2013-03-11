#include "UserCmdParser.hpp"
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

#include "UserCmdFusion.hpp"
#include "ParseGrammars.hpp"

// Uncomment to pass otherwise unknown commands un-parsed
//#define PARSE_RAW_STRING

namespace Iocaste {
    namespace Debugger {

template <typename Iterator>
struct UserCmdParseGrammar : qi::grammar<Iterator, UserCmd(), ascii::space_type>
{
    UserCmdParseGrammar() : UserCmdParseGrammar::base_type(start),
        gdb_value(gdb_value_parse_grammar())
    {
        raw_str = +qi::print;
        ident = +(qi::alpha | qi::char_('-'));
        file_name = +(qi::print -  qi::char_(':'));
        device_name = +(qi::print); // for tty
        value = +qi::char_;
        set_option = set_option_with_modifier | set_option_no_modifier;
        set_option_no_modifier = qi::lit("set") >> ident >> value >> qi::eoi;
        set_option_with_modifier = qi::lit("set") >> ident >> ident >> value >> qi::eoi;
        show_option = qi::lit("show") >> ident >> -ident;
        set_breakpoint = qi::lit("break") >> "\"" >> file_name >> ":" >> qi::int_ >> "\"";
        source = qi::lit("source") >> file_name;
        directory = qi::lit("directory") >> file_name;
        tty = qi::lit("tty") >> device_name;
        run = qi::lit("run") >> -value;
        info = qi::lit("info") >> value;
        backtrace = (qi::lit("bt")|qi::lit("backtrace")) >> qi::int_;

        step_mode = step_str | next_str | finish_str | cont_str;

        step_str = qi::string("step");
        next_str = qi::string("next");
        finish_str = qi::string("finish");
        cont_str = qi::string("cont");

        quit = qi::lit("quit") >> -value;
        return_ = qi::lit("return") >> -qi::lit(" ") >> -*qi::char_;
        pwd = qi::lit("pwd") >> -*qi::char_;
        what_is = (qi::string("whatis")|qi::string("output")) >> -*qi::char_;
        empty = qi::eps >> -value >> qi::eoi;
        start = set_option | show_option | set_breakpoint | source | directory | tty | run | info | backtrace
            | step_mode | quit | return_ | pwd | what_is | empty
        #ifdef PARSE_RAW_STRING
            | raw_str
        #endif
        ;
    }

    unique_ptr<qi::grammar<Iterator, SharedTypes::GdbValue()>> gdb_value;
    qi::rule<Iterator, std::string()> raw_str;
    qi::rule<Iterator, std::string()> ident;
    qi::rule<Iterator, std::string()> value;
    qi::rule<Iterator, std::string()> file_name;
    qi::rule<Iterator, std::string()> device_name;
    qi::rule<Iterator, std::string()> step_str;
    qi::rule<Iterator, std::string()> next_str;
    qi::rule<Iterator, std::string()> finish_str;
    qi::rule<Iterator, std::string()> cont_str;
    qi::rule<Iterator, UserCmds::SetOptionWithModifier(), ascii::space_type> set_option_with_modifier;
    qi::rule<Iterator, UserCmds::SetOptionNoModifier(), ascii::space_type> set_option_no_modifier;
    qi::rule<Iterator, UserCmds::SetOption(), ascii::space_type> set_option;
    qi::rule<Iterator, UserCmds::ShowOption(), ascii::space_type> show_option;
    qi::rule<Iterator, UserCmds::SetBreakpoint(), ascii::space_type> set_breakpoint;
    qi::rule<Iterator, UserCmds::Source(), ascii::space_type> source;
    qi::rule<Iterator, UserCmds::Directory(), ascii::space_type> directory;
    qi::rule<Iterator, UserCmds::TTY(), ascii::space_type> tty;
    qi::rule<Iterator, UserCmds::Run(), ascii::space_type> run;
    qi::rule<Iterator, UserCmds::Info(), ascii::space_type> info;
    qi::rule<Iterator, UserCmds::Backtrace(), ascii::space_type> backtrace;
    qi::rule<Iterator, UserCmds::StepMode(), ascii::space_type> step_mode;
    qi::rule<Iterator, UserCmds::Quit(), ascii::space_type> quit;
    qi::rule<Iterator, UserCmds::PrintWorkingDirectory(), ascii::space_type> pwd;
    qi::rule<Iterator, UserCmds::Return(), ascii::space_type> return_;
    qi::rule<Iterator, UserCmds::WhatIs(), ascii::space_type> what_is;
    qi::rule<Iterator, UserCmds::Empty(), ascii::space_type> empty;
    qi::rule<Iterator, UserCmd(), ascii::space_type> start;
};


UserCmd UserCmdParser::Parse(std::string str) const
{
    using boost::spirit::ascii::space;
    typedef std::string::const_iterator iterator_type;
    typedef UserCmdParseGrammar<iterator_type> UserCmdGrammar;

    UserCmdGrammar g; // Our grammar

    std::string::const_iterator iter = str.begin();
    std::string::const_iterator end = str.end();
    UserCmd result;
    bool success = phrase_parse(iter, end, g, space, result);

    if (!success)
    {
        stringstream ss;
        ss << "UserCmdParser failed to parse: " << str << std::endl;
        cerr << endl << ss.str() << endl;
        raiseError(ParseException(ss.str()));
    }
    else
    {
        if (iter != end)
        {
            stringstream ss;
            ss << "Not all of the line was parsed: " << std::string(iter, end) << std::endl;
            cerr << endl << ss.str() << endl;
            raiseError(ParseException(ss.str()));
        }
    }

    return result;
}


UserCmdParser::UserCmdParser(AbstractOutput<UserCmd>& sink_)
    : sink(sink_)
{
}

void UserCmdParser::WriteData(std::string const& input)
{
    UserCmd cmd = Parse(input);
    sink.WriteData(cmd);
}

    }
}
