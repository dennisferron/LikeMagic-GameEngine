#include "BreakpointManager.hpp"

using namespace Iocaste::Debugger;

#include "boost/algorithm/string/predicate.hpp"


BreakpointManager::BreakpointManager(MainChannels const& channels_)
    : channels(channels_), gdb_prompt("(gdb) ") {}

void BreakpointManager::setPrompt(std::string new_prompt)
{
    gdb_prompt = new_prompt;
}

void BreakpointManager::toGdb(UserCmd const& cmd) const
{
    channels.toGdb.WriteData(cmd);
}

void BreakpointManager::toUser(GdbResponse const& response) const
{
    channels.toUser.WriteData(response);
}

OurBreakpoint BreakpointManager::setIoDebuggerBreakpoint(std::string function_name)
{
    UserCmds::SetBreakpointOnFunction real_bkpt = { function_name };
    UserCmd cmd;
    cmd = real_bkpt;
    channels.toGdb.WriteData( cmd );

    GdbResponse resp = channels.fromGdb.ReadData();

    if (auto* bs = boost::get<GdbResponses::BreakpointSet>(&resp.values.at(0)))
    {
        GdbBreakpoint gb = { bs->breakpoint_number };
        return brkpts.get_user_breakpoint<OurBreakpoint>(gb);
    }
    else
    {
        raiseError(BadResponseError("Did not get expected gdb response type from gdb when setting breakpoint on " + function_name + "() function."));

        // never get here
        return {-1};
    }
}

void BreakpointManager::loadDeferredBreakpoint(SharedTypes::GdbAddress io_state, IoBreakpoint ib)
{
    UserCmds::PrintFunction print;
    print.function_name = "io_debugger_set_breakpoint";
    print.args.push_back( { io_state } );
    print.args.push_back( { ib.number } );
    print.args.push_back( { ib.file_name } );
    print.args.push_back( { ib.line_number } );
    channels.toGdb.WriteData(print);

    GdbResponse resp = channels.fromGdb.ReadData();

    if (auto* vh = boost::get<GdbResponses::ValueHistory>(&resp.values.at(0)))
    {
        if (auto* breakpt_num = boost::get<int>(&(vh->value.value)))
        {
            // If the breakpoint was set correctly, the function will return the breakpoint number.
            if (*breakpt_num != ib.number)
                raiseError(BadResponseError("Did not get expected return value when calling io_debugger_set_breakpoint."));
            else
                return;  // ok
        }
        else
        {
            raiseError(BadResponseError("Did not get expected function return type from gdb when calling io_debugger_set_breakpoint."));
        }
    }
    else
    {
        raiseError(BadResponseError("Did not get expected gdb response type from gdb when calling io_debugger_set_breakpoint."));
    }
}

IoBreakpoint BreakpointManager::setIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
{
    if (!io_init_breakpoint)
        io_init_breakpoint = setIoDebuggerBreakpoint("io_debugger_init");

    if (!io_debugger_breakpoint)
        io_debugger_breakpoint = setIoDebuggerBreakpoint("io_debugger_break_here");

    IoBreakpoint ib;
    ib.file_name = stbk.file_name;
    ib.file_name = stbk.line_number;
    ib.number = deferred_breakpoints.size();
    deferred_breakpoints.push_back(ib);

    return ib;
}

void BreakpointManager::userSetIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
{
    IoBreakpoint ib = setIoBreakpoint(stbk);
    UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(ib);

    GdbResponses::BreakpointSet bs;

    bs.breakpoint_number = ub.number;
    bs.address = { "0x00000000" };
    bs.file_name = stbk.file_name;
    bs.line_number = stbk.line_number;

    GdbResponse resp;
    resp.prompt = gdb_prompt;
    resp.values.push_back(bs);
    toUser(resp);
}

GdbResponses::BreakpointSet BreakpointManager::setGdbBreakpoint(UserCmds::SetBreakpoint const& stbk)
{
    channels.toGdb.WriteData(stbk);

    GdbResponse resp = channels.fromGdb.ReadData();

    if (auto* bs = boost::get<GdbResponses::BreakpointSet>(&resp.values.at(0)))
    {
        return *bs;
    }
    else
    {
        raiseError(BadResponseError("Did not get expected gdb response type from gdb when calling set breakpoint."));
    }

    // Never get here
    return GdbResponses::BreakpointSet();
}

void BreakpointManager::userSetGdbBreakpoint(UserCmds::SetBreakpoint const& stbk)
{
    GdbResponses::BreakpointSet bs = setGdbBreakpoint(stbk);

    GdbBreakpoint gb = { bs.breakpoint_number };
    UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(gb);

    bs.breakpoint_number = ub.number;

    GdbResponse resp;
    resp.prompt = gdb_prompt;
    resp.values.push_back(bs);
    toUser(resp);
}

BreakpointManager::FunctionArgs BreakpointManager::getArgs()
{
    toGdb( UserCmds::Info { "args" } );
    GdbResponse resp = channels.fromGdb.ReadData();

    BreakpointManager::FunctionArgs result;

    for (auto item : resp.values)
    {
        if (auto* locals = boost::get<GdbResponses::LocalsInfo>(&item))
        {
            if (auto* nl = boost::get<SharedTypes::NoLocals>(&(locals->value)))
                result.push_back( std::make_pair(nl->text, SharedTypes::GdbValue()) );
            else if (auto* veq = boost::get<SharedTypes::VariableEquals>(&(locals->value)))
                result.push_back({ veq->name, veq->value });
            else
                raiseError(BadResponseError("Did not get expected LocalsInfo line from gdb when calling info locals."));
        }
        else
            raiseError(BadResponseError("Did not get expected gdb response type from gdb when calling info locals."));
    }

    return result;
}

SharedTypes::GdbValue BreakpointManager::getArg(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    for (auto arg : args)
        if (arg.first == arg_name)
            return arg.second;

    raiseError(BadResponseError("Did not find expected arg " + arg_name + " in gdb response to info locals."));

    // Never get here
    return {};
}

int BreakpointManager::getInt(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    auto value = getArg(args, arg_name);

    if (auto* result = boost::get<int>(&(value.value)))
        return *result;
    else
        raiseError(BadResponseError("Did not get expected LocalsInfo variable type for arg " + arg_name + " from gdb when calling info locals."));

    // Never get here.
    return -1;
}

std::string BreakpointManager::getValueAsString(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    auto value = getArg(args, arg_name);

    if (value.value_as_string)
        return value.value_as_string->text;
    else
        raiseError(BadResponseError("Did not get value_as_string in LocalsInfo variable for arg " + arg_name + " from gdb when calling info locals."));

    // Never get here.
    return "";
}

SharedTypes::GdbAddress BreakpointManager::getPointer(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    auto value = getArg(args, arg_name);

    if (auto* result = boost::get<SharedTypes::GdbAddress>(&(value.value)))
        return *result;
    else
        raiseError(BadResponseError("Did not get expected LocalsInfo variable type for arg " + arg_name + " from gdb when calling info locals."));

    // Never get here
    return SharedTypes::GdbAddress();
}

void BreakpointManager::ioDebuggerInit()
{
    // At inferior function "io_debugger_init"

    auto args = getArgs();
    SharedTypes::GdbAddress io_state = getPointer(args, "io_state");

    for (IoBreakpoint ib : deferred_breakpoints)
    {
        loadDeferredBreakpoint(io_state, ib);
    }

    // Give the user the illusion the breakpoint was never hit.
    toGdb( UserCmds::Cont {"cont"} );
}

GdbResponseType BreakpointManager::ioDebuggerIoBreakpoint()
{
    // At inferior function "io_debugger_break_here"

    auto args = getArgs();
    auto self = getPointer(args, "self");
    auto locals = getPointer(args, "locals");
    auto m = getPointer(args, "m");
    int breakpoint_number = getInt(args, "breakpoint_number");
    std::string file_name = getValueAsString(args, "file_name");
    int line_number = getInt(args, "line_number");

    // TODO:  Save self,locals,m to use when evaluating watches on Io code

    GdbResponses::BreakpointHit bh;

    bh.breakpoint_number = breakpoint_number;
    // bh.function = {}; TODO:  Get message name and argument names.
    bh.file_name = file_name;
    bh.line_number = line_number;

    return bh;
}

void BreakpointManager::userSetBreakpoint(const UserCmds::SetBreakpoint& t)
{
    if (boost::algorithm::ends_with(t.file_name, ".io"))
        userSetIoBreakpoint(t);
    else
        userSetGdbBreakpoint(t);
}

GdbResponseType BreakpointManager::gdbBreakpointSet(const GdbResponses::BreakpointSet& t)
{
    GdbResponses::BreakpointSet bs(t);
    GdbBreakpoint gb = {t.breakpoint_number};
    bs.breakpoint_number = brkpts.get_user_breakpoint<UserBreakpoint>(gb).number;
    return bs;
}

GdbResponseType BreakpointManager::gdbBreakpointHit(const GdbResponses::BreakpointHit& t)
{
    GdbBreakpoint gb = { t.breakpoint_number };

    if (brkpts.has_user_breakpoint<OurBreakpoint>(gb))
    {
        OurBreakpoint ob = brkpts.get_user_breakpoint<OurBreakpoint>(gb);

        if (ob == *io_init_breakpoint)
        {
            ioDebuggerInit();
            return GdbResponses::Empty();
        }
        else if (ob == *io_debugger_breakpoint)
        {
            return ioDebuggerIoBreakpoint();
        }
        else
        {
            raiseError(LogicError("Hit one of 'our' internal debugger breakpoints, but it does not match the ones we set."));
            return GdbResponses::Empty();
        }
    }
    else
    {
        GdbResponses::BreakpointHit bh(t);
        bh.breakpoint_number = brkpts.get_user_breakpoint<UserBreakpoint>(gb).number;
        return bh;
    }
}
