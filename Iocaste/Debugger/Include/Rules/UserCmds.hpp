#include "SpiritMacros.hpp"

// Do NOT define #pragma once in rules headers.

    unique_ptr<qi::grammar<Iterator, Rules::GdbValue()>> gdb_value;
    qi::rule<Iterator, std::string()> raw_str;
        raw_str = +qi::print;
    qi::rule<Iterator, std::string()> ident;
        ident = +(qi::alpha | qi::char_('-'));
    qi::rule<Iterator, std::string()> value;
        value = +qi::char_;
    qi::rule<Iterator, std::string()> file_name;
        file_name = +(qi::print -  qi::char_(':'));
    qi::rule<Iterator, std::string()> device_name;
        device_name = +(qi::print); // for tty
    qi::rule<Iterator, std::string()> step_str;
        step_str = qi::string("step");
    qi::rule<Iterator, std::string()> next_str;
        next_str = qi::string("next");
    qi::rule<Iterator, std::string()> finish_str;
        finish_str = qi::string("finish");
    qi::rule<Iterator, std::string()> cont_str;
        cont_str = qi::string("cont");
    qi::rule<Iterator, Rules::SetOptionWithModifier(), ascii::space_type> set_option_with_modifier;
        set_option_with_modifier = qi::lit("set") >> ident >> ident >> value >> qi::eoi;
    qi::rule<Iterator, Rules::SetOptionNoModifier(), ascii::space_type> set_option_no_modifier;
        set_option_no_modifier = qi::lit("set") >> ident >> value >> qi::eoi;
    qi::rule<Iterator, Rules::SetOption(), ascii::space_type> set_option;
        set_option = set_option_with_modifier | set_option_no_modifier;
    qi::rule<Iterator, Rules::ShowOption(), ascii::space_type> show_option;
        show_option = qi::lit("show") >> ident >> -ident;
    qi::rule<Iterator, Rules::SetBreakpoint(), ascii::space_type> set_breakpoint;
        set_breakpoint = qi::lit("break") >> "\"" >> file_name >> ":" >> qi::int_ >> "\"";
    qi::rule<Iterator, Rules::Source(), ascii::space_type> source;
        source = qi::lit("source") >> file_name;
    qi::rule<Iterator, Rules::Directory(), ascii::space_type> directory;
        directory = qi::lit("directory") >> file_name;
    qi::rule<Iterator, Rules::TTY(), ascii::space_type> tty;
        tty = qi::lit("tty") >> device_name;
    qi::rule<Iterator, Rules::Run(), ascii::space_type> run;
        run = qi::lit("run") >> -value;
    qi::rule<Iterator, Rules::Info(), ascii::space_type> info;
        info = qi::lit("info") >> value;
    qi::rule<Iterator, Rules::Backtrace(), ascii::space_type> backtrace;
        backtrace = (qi::lit("bt")|qi::lit("backtrace")) >> qi::int_;
    qi::rule<Iterator, Rules::StepMode(), ascii::space_type> step_mode;
        step_mode = step_str | next_str | finish_str | cont_str;
    qi::rule<Iterator, Rules::Quit(), ascii::space_type> quit;
        quit = qi::lit("quit") >> -value;
    qi::rule<Iterator, Rules::PrintWorkingDirectory(), ascii::space_type> pwd;
        pwd = qi::lit("pwd") >> -*qi::char_;
    qi::rule<Iterator, Rules::Return(), ascii::space_type> return_;
        return_ = qi::lit("return") >> -qi::lit(" ") >> -*qi::char_;
    qi::rule<Iterator, Rules::WhatIs(), ascii::space_type> what_is;
        what_is = (qi::string("whatis")|qi::string("output")) >> -*qi::char_;
    qi::rule<Iterator, Rules::Empty(), ascii::space_type> empty;
        empty = qi::eps >> -value >> qi::eoi;
    qi::rule<Iterator, UserCmd(), ascii::space_type> start;

        start = set_option | show_option | set_breakpoint | source | directory | tty | run | info | backtrace
            | step_mode | quit | return_ | pwd | what_is | empty
        #ifdef PARSE_RAW_STRING
            | raw_str
        #endif
        ;
