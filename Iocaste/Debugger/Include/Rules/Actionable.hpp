
#include "SpiritMacros.hpp"

// Do NOT define #pragma once in rules headers.

SPIRIT_STRUCT((IoDbg)(Rules),
    ProgramExited,
        (std::string, how),
    program_exited,
        qi::lit("Program exited ") > program_exited_str,
        karma::lit("Program exited ") << karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    WorkingDirectory,
        (std::string, directory),
    working_directory,
        qi::lit("Working directory ") > up_to_last_period > '.',
        karma::lit("Working directory ") << karma::string << "."
)

SPIRIT_STRUCT((IoDbg)(Rules),
    TypeEquals,
        (std::string, type),
    type_equals,
        qi::lit("type = ") > +qi::char_,
        karma::lit("type = ") << karma::string
)

SPIRIT_STRUCT((IoDbg)(Rules),
    Empty,
        (boost::optional<std::string>, dummy),
    empty,
        qi::lit("") >> -*qi::char_('`') >> qi::eoi,
        karma::lit("") << -dummy
)

SPIRIT_STRUCT((IoDbg)(Rules),
    BreakpointSet,
        (int, breakpoint_number)
        (Rules::GdbAddress, address)
        (std::string, file_name)
        (int, line_number),
    breakpoint_set,
        qi::lit("Breakpoint ") >> qi::int_ >> " at " >> address >> ": file " >> file_name >> "," >> " line " >> qi::int_ >> ".",
        karma::lit("Breakpoint ") << karma::int_ << " at " << address << ": file " << file_name << ", line " << karma::int_ << "."
)

SPIRIT_STRUCT((IoDbg)(Rules),
    BreakpointHit,
        (int, breakpoint_number)
        (Rules::GdbResponseFunction, function)
        (std::string, file_name)
        (int, line_number),
        breakpoint_hit,
            qi::lit("Breakpoint ") >> qi::int_ >> ", " > gdb_function > " at " > file_name > ":" > qi::int_,
            karma::lit("Breakpoint ") << karma::int_ << ", " << gdb_function << " at " << file_name << ":" << karma::int_
)

SPIRIT_STRUCT((IoDbg)(Rules),
    BreakpointPending,
        (int, breakpoint_number)
        (std::string, func_name),
        breakpoint_pending,
            qi::lit("Breakpoint ") >> qi::int_ >> " (" >> *(qi::char_ - qi::char_(')')) >> ") pending.",
            karma::lit("Breakpoint ") << karma::int_ << " (" << karma::string << ") pending.";
)

SPIRIT_STRUCT((IoDbg)(Rules),
    AddressInFunction,
        (Rules::AddressIn, address_in)
        (Rules::GdbResponseFunction, function),
    address_in_function,
        address_in >> gdb_function,
        address_in << gdb_function
)

SPIRIT_STRUCT((IoDbg)(Rules),
    BacktraceLine,
        (int, backtrace_number)
        (std::string, spaces)
        (boost::optional<
            Rules::AddressIn
        >, address_in)
        (Rules::GdbResponseFunction, function)
        (boost::optional<
            Rules::FromModule
        >, module)
        (boost::optional<
            Rules::AtFile
        >, file_name)
        (boost::optional<
            int
        >, line_number),
    backtrace_line,
        qi::lit("#") > qi::int_ > +qi::space
            > -address_in
            > gdb_function
            > -from_module
            > -at_file
            > -(qi::lit(":") > qi::int_),
        karma::lit("#") << karma::int_ << karma::string
            << -address_in
            << gdb_function
            << -from_module
            << -at_file
            << -(karma::lit(":") << karma::int_)
)

SPIRIT_STRUCT((IoDbg)(Rules),
    CursorPos,
        (std::string, file_name)
        (int, line_number)
        (int, char_number)
        (std::string, unknown)
        (Rules::GdbAddress, address),
    cursor_pos,
        qi::lit("\x1A\x1A") >> file_name >> ":" >> qi::int_ >> ":" >> qi::int_ >> ":" >> *qi::alpha >> ":" >> address,
        karma::lit("\x1A\x1A") << file_name << ":" << karma::int_ << ":" << karma::int_ << ":" << karma::string << ":" << address
)

#ifdef DECL_STRUCTS
namespace IoDbg { namespace Rules {
    typedef boost::variant<
        Rules::NoLocals,
        Rules::VariableEquals
    > LocalsInfo_locals_type;
}}
#endif

SPIRIT_STRUCT((IoDbg)(Rules),
    LocalsInfo,
        (LocalsInfo_locals_type, value),
    locals_info,
        no_locals | variable_equals,
        karma::lit("") << (no_locals | variable_equals)
)

SPIRIT_STRUCT((IoDbg)(Rules),
    ValueHistory,
        (int, number)
        (std::string, equals)
        (GdbValue, value),
    value_history,
        qi::lit('$') >> qi::int_ >> equals >> gdb_value,
        karma::lit('$') << karma::int_ << equals << gdb_value
)

SPIRIT_STRUCT((IoDbg)(Rules),
    OutputValue,
        (GdbValue, value),
    output_value,
        gdb_value,
        gdb_value
)

#ifdef DECL_STRUCTS
namespace IoDbg { namespace Rules {

typedef  boost::variant
<
    Rules::Empty,
    Rules::BreakpointSet,
    Rules::CursorPos,
    Rules::BreakpointHit,
    Rules::BreakpointPending,
    Rules::LocalsInfo,
    Rules::BacktraceLine,
    Rules::ValueHistory,
    Rules::ProgramExited,
    Rules::AddressInFunction,
    Rules::WorkingDirectory,
    Rules::TypeEquals
> GdbActionableType;

}}
#endif

SPIRIT_RULE((IoDbg)(Rules), GdbActionableType,
    actionable_variant,
        locals_info | backtrace_line,
        locals_info | backtrace_line
)
// TODO:  figure out which of these was causing the compile error, and restore the rule.
//        locals_info | backtrace_line | banner | breakpoint_set | breakpoint_hit | cursor_pos | address_in_function | program_exited | working_directory | type_equals | empty,
//        locals_info | backtrace_line | banner | breakpoint_set | breakpoint_hit | cursor_pos | address_in_function | program_exited | working_directory | type_equals | empty
//)


SPIRIT_STRUCT((IoDbg)(Rules),
    GdbActionable,
        (GdbActionableType, value),
    actionable,
        breakpoint_set | breakpoint_pending | cursor_pos | breakpoint_hit | locals_info | address_in_function
            | backtrace_line | value_history | program_exited | working_directory | type_equals | empty,
        actionable = actionable_variant << karma::lit("\n")
)

#ifdef DECL_STRUCTS
namespace IoDbg { namespace Rules {

typedef boost::variant
<
    Rules::OutputValue
> GdbContextSensitiveType;

}}
#endif

SPIRIT_RULE((IoDbg)(Rules), GdbContextSensitiveType,
    context_sens_variant,
        output_value | output_value,
        output_value | output_value
)


SPIRIT_STRUCT((IoDbg)(Rules),
    GdbContextSensitive,
        (GdbContextSensitiveType, value),
    context_sens,
        output_value,
        context_sens_variant
)

#ifdef DECL_STRUCTS
namespace IoDbg { namespace Rules {

typedef boost::variant
<
    GdbUnactionable,
    GdbActionable,
    GdbContextSensitive
> GdbResponseType;

}}
#endif

SPIRIT_RULE((IoDbg)(Rules), GdbResponseType,
    response_item,
        actionable | unactionable | context_sens,
        actionable | unactionable | context_sens
)
