#pragma once

#include "SharedTypes.hpp"

namespace Iocaste { namespace Debugger {

namespace GdbResponses
{

struct Banner
{
    std::string version;
    std::string msg;
};

struct Empty
{
    boost::optional<std::string> dummy;
};

struct RawStr
{
    std::string value;
};

struct ReadingSymbols
{
    std::string message;
};

struct BreakpointSet
{
    int breakpoint_number;
    SharedTypes::GdbAddress address;
    std::string file_name;
    int line_number;
};

struct BreakpointPending
{
    int breakpoint_number;
    std::string func_name;
};

struct CursorPos
{
    std::string file_name;
    int line_number;
    int char_number;
    std::string unknown;
    SharedTypes::GdbAddress address;
};

struct BreakpointHit
{
    int breakpoint_number;
    SharedTypes::GdbResponseFunction function;
    std::string file_name;
    int line_number;
};

struct LocalsInfo
{
    typedef boost::variant<
        SharedTypes::NoLocals,
        SharedTypes::VariableEquals
    > locals_type;
    locals_type value;
};

/*
#0  m4_traceon (obs=0x24eb0, argc=1, argv=0x2b8c8) at builtin.c:993
#1  0x6e38 in expand_macro (sym=0x2b600) at macro.c:242
#2  0x6840 in expand_token (obs=0x0, t=177664, td=0xf7fffb08) at macro.c:71

#0  func2 (x=30) at test.c:5
#1  0x80483e6 in func1 (a=30) at test.c:10
#2  0x8048414 in main (argc=1, argv=0xbffffaf4) at test.c:19
#3  0x40037f5c in __libc_start_main () from /lib/libc.so.6

#0  0xb80c5430 in __kernel_vsyscall ()
#1  0xb7d1b6d0 in raise () from /lib/tls/i686/cmov/libc.so.6
#2  0xb7d1d098 in abort () from /lib/tls/i686/cmov/libc.so.6
#3  0xb7d5924d in ?? () from /lib/tls/i686/cmov/libc.so.6
#4  0xb7d62276 in ?? () from /lib/tls/i686/cmov/libc.so.6
#5  0xb7d639c5 in malloc () from /lib/tls/i686/cmov/libc.so.6
#6  0xb7f42f47 in operator new () from /usr/lib/libstdc++.so.6
#7  0x0805bd20 in Image<Color>::fft (this=0xb467640) at ../image_processing/image.cpp:545
*/

// address in qual::function (args=value) at file:line

// -(address in) (function|?? (args)) ((at file:line)(from module))

// #0  main () at /Users/dennisferron/code/LikeMagic-All/Iocaste/Debugger/TestProject/main.cpp:7
// #0  0x0000000100000e20 in start ()
struct BacktraceLine
{
    int backtrace_number;

    std::string spaces;

    boost::optional<
        SharedTypes::AddressIn
    > address_in;

    SharedTypes::GdbResponseFunction function;

    boost::optional<
        SharedTypes::FromModule
    > module;

    boost::optional<
        SharedTypes::AtFile
    > file_name;

    boost::optional<
        int
    > line_number;
};


struct AddressInFunction
{
    SharedTypes::AddressIn address_in;
    SharedTypes::GdbResponseFunction function;
};

struct ValueHistory
{
    int number;
    std::string equals;
    SharedTypes::GdbValue value;
};

struct SquareBracketMsg
{
    std::string msg;
};

struct SignalReceived
{
    std::string msg;
};

struct TestStr1
{
    std::string value;
};

struct TestStr2
{
    std::string value;
};

struct UninitializedVariant
{
    double dummy;
};

struct ProgramExited
{
    std::string how;
};

struct WorkingDirectory
{
    std::string directory;
};

}


typedef  boost::variant
<
    GdbResponses::UninitializedVariant,
    GdbResponses::ReadingSymbols,
    GdbResponses::BreakpointSet,
    GdbResponses::CursorPos,
    GdbResponses::BreakpointHit,
    GdbResponses::BreakpointPending,
    GdbResponses::LocalsInfo,
    GdbResponses::BacktraceLine,
    GdbResponses::Banner,
    GdbResponses::ValueHistory,
    GdbResponses::RawStr,
    GdbResponses::ProgramExited,
    GdbResponses::SquareBracketMsg,
    GdbResponses::SignalReceived,
    GdbResponses::AddressInFunction,
    GdbResponses::WorkingDirectory,
    GdbResponses::Empty
> GdbResponseType;


struct GdbResponse
{
    std::vector<GdbResponseType> values;
    std::string prompt;
};

}}
