#include "BreakpointManager.hpp"

using namespace Iocaste::Debugger;

#include "boost/algorithm/string/predicate.hpp"
#include "boost/lexical_cast.hpp"

using namespace std;

#include <stdlib.h>

namespace Iocaste { namespace Debugger {

struct BreakpointResponseVisitor : boost::static_visitor<GdbResponseType>
{
    bool hit_io_breakpoint;
    BreakpointManager& bkpt_mgr;

    BreakpointResponseVisitor(BreakpointManager& bkpt_mgr_)
        : hit_io_breakpoint(false), bkpt_mgr(bkpt_mgr_) {}

    template <typename T>
    GdbResponseType operator()(const T& t)
    {
        return t;
    }

    GdbResponseType operator()(const GdbResponses::BreakpointSet& t)
    {
        return bkpt_mgr.gdbBreakpointSet(t);
    }

    GdbResponseType operator()(const GdbResponses::BreakpointHit& t)
    {
        return bkpt_mgr.gdbBreakpointHit(t, hit_io_breakpoint);
    }

    GdbResponseType operator()(const GdbResponses::CursorPos& t)
    {
        return bkpt_mgr.gdbCursorPos(t, hit_io_breakpoint);
    }
};

}}

BreakpointManager::BreakpointManager(MainChannels const& channels_)
    : channels(channels_), gdb_prompt("(gdb) ")
{
}

void BreakpointManager::handle(GdbResponse const& response)
{
    BreakpointResponseVisitor visitor(*this);

    std::vector<GdbResponseType> output;
    for (auto line_item : response.values)
        output.push_back(boost::apply_visitor(visitor, line_item));

    bool all_empty = true;
    for (auto item : output)
        if (!boost::get<GdbResponses::Empty>(&item))
            all_empty = false;

    if (!all_empty)
    {
        GdbResponse munged;
        munged.prompt = response.prompt;
        munged.values = output;
        channels.toUser.WriteData(munged);
    }
}

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
        OurBreakpoint result = brkpts.get_user_breakpoint<OurBreakpoint>(gb);
        channels.info.WriteData("Mapped gdb breakpoint #" + boost::lexical_cast<string>(bs->breakpoint_number)
            + " to our breakpoint #" + boost::lexical_cast<string>(result.number));
        return result;
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
    ib.line_number = stbk.line_number;
    ib.number = deferred_breakpoints.size()+1;
    deferred_breakpoints.push_back(ib);

    return ib;
}

void BreakpointManager::userSetIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
{
    IoBreakpoint ib = setIoBreakpoint(stbk);
    UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(ib);

    GdbResponses::BreakpointSet bs;

    bs.breakpoint_number = ub.number;
    bs.address = { "00000000" };
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

// I wrote this function for getting the args using info args,
// but then realized I already could get the args from the BreakpointHit struct.
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

BreakpointManager::FunctionArgs BreakpointManager::getArgs(SharedTypes::GdbResponseFunction func)
{
    BreakpointManager::FunctionArgs result;

    for (auto arg : func.args)
    {
        result.push_back({ arg.name, arg.value });
    }

    return result;
}

SharedTypes::GdbValue BreakpointManager::getArg(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    for (auto arg : args)
        if (arg.first == arg_name)
            return arg.second;

    raiseError(BadResponseError("Did not find expected arg " + arg_name + " in gdb response to info args or breakpoint hit."));

    // Never get here
    return {};
}

int BreakpointManager::getInt(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    auto value = getArg(args, arg_name);

    if (auto* result = boost::get<int>(&(value.value)))
        return *result;
    else
        raiseError(BadResponseError("Did not get expected type for arg " + arg_name + " from gdb info args or breakpoint hit args."));

    // Never get here.
    return -1;
}

std::string BreakpointManager::getValueAsString(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    auto value = getArg(args, arg_name);

    if (value.value_as_string)
        return value.value_as_string->text;
    else
        raiseError(BadResponseError("Did not get value_as_string for arg " + arg_name + " from gdb info args or breakpoint hit args."));

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

void BreakpointManager::ioDebuggerInit(const GdbResponses::BreakpointHit& bh)
{
    // At inferior function "io_debugger_init"

    auto args = getArgs(bh.function);
    SharedTypes::GdbAddress io_state = getPointer(args, "io_state");

    for (IoBreakpoint ib : deferred_breakpoints)
    {
        loadDeferredBreakpoint(io_state, ib);
    }

    // Give the user the illusion the breakpoint was never hit.
    toGdb( UserCmds::Cont {"cont"} );
}

GdbResponseType BreakpointManager::ioDebuggerIoBreakpoint(const GdbResponses::BreakpointHit& bh)
{
    // At inferior function "io_debugger_break_here"

    auto args = getArgs(bh.function);
    auto self = getPointer(args, "self");
    auto locals = getPointer(args, "locals");
    auto m = getPointer(args, "m");
    int breakpoint_number = getInt(args, "breakpoint_number");
    std::string file_name = getValueAsString(args, "file_name");
    int line_number = getInt(args, "line_number");

    // TODO:  Save self,locals,m to use when evaluating watches on Io code

    GdbResponses::BreakpointHit bh_spoof;
    bh_spoof.breakpoint_number = breakpoint_number;
    // bh_spoof.function = {}; TODO:  Get message name and argument names.
    bh_spoof.file_name = file_name;
    bh_spoof.line_number = line_number;

    GdbResponses::CursorPos cp_spoof;
    cp_spoof.file_name = file_name;
    cp_spoof.line_number = line_number;
    cp_spoof.char_number = 1;
    cp_spoof.unknown = "beg";
    cp_spoof.address = { "00000000" };

    GdbResponse resp_spoof;
    resp_spoof.prompt = gdb_prompt;
    resp_spoof.values.push_back(GdbResponses::Empty());
    resp_spoof.values.push_back(bh_spoof);
    resp_spoof.values.push_back(cp_spoof);

    channels.toUser.WriteData(resp_spoof);

    return GdbResponses::Empty();
}

bool BreakpointManager::isIoBreakpoint(string file_name) const
{
    return
        boost::algorithm::ends_with(file_name, ".io") ||
        boost::algorithm::ends_with(file_name, "inl.io");
}

void BreakpointManager::userSetBreakpoint(const UserCmds::SetBreakpoint& t)
{
    if (isIoBreakpoint(t.file_name))
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

GdbResponseType BreakpointManager::gdbBreakpointHit(const GdbResponses::BreakpointHit& t, bool& is_our_breakpoint)
{
    GdbBreakpoint gb = { t.breakpoint_number };

    if (brkpts.has_user_breakpoint<OurBreakpoint>(gb))
    {
        is_our_breakpoint = true;
        OurBreakpoint ob = brkpts.get_user_breakpoint<OurBreakpoint>(gb);
        channels.info.WriteData("Mapped gdb breakpoint " + boost::lexical_cast<string>(gb.number)
            + " to our breakpoint " + boost::lexical_cast<string>(ob.number));

        if (ob == *io_init_breakpoint)
        {
            ioDebuggerInit(t);
            return GdbResponses::Empty();
        }
        else if (ob == *io_debugger_breakpoint)
        {
            return ioDebuggerIoBreakpoint(t);
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

GdbResponseType BreakpointManager::gdbCursorPos(const GdbResponses::CursorPos& t, bool hit_our_breakpoint)
{
    // Suppress returning the cursor position if the breakpoint is one of ours.
    if (hit_our_breakpoint)
        return GdbResponses::Empty();
    else
        return t;
}
