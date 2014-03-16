#include "Rules/RuleStructs.hpp"

#include "BreakpointManager.hpp"
#include "WatchManager.hpp"

using namespace IoDbg;
using namespace IoDbg::Rules;

#include "boost/algorithm/string/predicate.hpp"
#include "boost/lexical_cast.hpp"

#define BOOST_FILESYSTEM_VERSION 3
#include "boost/filesystem.hpp"
namespace fs = boost::filesystem;

using namespace std;

#include <stdlib.h>

namespace IoDbg {

struct BreakpointResponseVisitor : boost::static_visitor<GdbActionable>
{
    bool hit_io_breakpoint;
    BreakpointManager& bkpt_mgr;
    WatchManager& watch_mgr;

    BreakpointResponseVisitor(BreakpointManager& bkpt_mgr_, WatchManager& watch_mgr_)
        : hit_io_breakpoint(false), bkpt_mgr(bkpt_mgr_), watch_mgr(watch_mgr_) {}

    template <typename T>
    GdbActionable operator()(const T& t)
    {
        return {t};
    }

    GdbActionable operator()(const Rules::BreakpointSet& t)
    {
        return bkpt_mgr.gdbBreakpointSet(t);
    }

    GdbActionable operator()(const Rules::BreakpointPending& t)
    {
        return bkpt_mgr.gdbBreakpointPending(t);
    }

    GdbActionable operator()(const Rules::BreakpointHit& t)
    {
        return bkpt_mgr.gdbBreakpointHit(t, hit_io_breakpoint);
    }

    GdbActionable operator()(const Rules::CursorPos& t)
    {
        return bkpt_mgr.gdbCursorPos(t, hit_io_breakpoint);
    }
};

}


BreakpointManager::BreakpointManager(MainChannels const& channels_, WatchManager& watch_mgr_)
    : channels(channels_), watch_mgr(watch_mgr_), gdb_prompt("(gdb) ")
{
}

bool BreakpointManager::handle(GdbResponse const& response)
{
    BreakpointResponseVisitor visitor(*this, watch_mgr);

    std::vector<GdbResponseType> output;
    for (auto line_item : response.values)
        output.push_back(visitIfActionable(visitor, line_item));

/*
        if (GdbActionable* a = boost::get<GdbActionable>(&line_item))
            output.push_back(boost::apply_visitor(visitor, *a));
        else
            output.push_back(line_item);
*/

    bool all_empty = true;
    for (auto item : output)
        if (!boost::get<Rules::Empty>(&item))
            all_empty = false;

    if (!all_empty)
    {
        GdbResponse munged;
        munged.prompt = response.prompt;
        munged.values = output;
        channels.toUser.WriteData(munged);
    }

    return visitor.hit_io_breakpoint;
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
    Rules::SetBreakpointOnFunction real_bkpt = { function_name };
    UserCmd cmd;
    cmd = real_bkpt;
    channels.toGdb.WriteData( cmd );

    GdbResponse resp = channels.fromGdb.ReadData();

    if (auto* bs = getActionable<Rules::BreakpointSet>(&resp.values.at(0)))
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

void BreakpointManager::loadDeferredBreakpoint(Rules::GdbAddress io_state, IoBreakpoint ib)
{
    Rules::PrintFunction print;
    print.function_name = "io_debugger_set_breakpoint";
    print.args.push_back( { io_state } );
    print.args.push_back( { ib.number } );
    print.args.push_back( { ib.file_name } );
    print.args.push_back( { ib.line_number } );
    channels.toGdb.WriteData(print);

    GdbResponse resp = channels.fromGdb.ReadData();

    if (auto* vh = getActionable<Rules::ValueHistory>(&resp.values.at(0)))
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

IoBreakpoint BreakpointManager::setIoBreakpoint(Rules::SetBreakpoint const& stbk)
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

void BreakpointManager::userSetIoBreakpoint(Rules::SetBreakpoint const& stbk)
{
    IoBreakpoint ib = setIoBreakpoint(stbk);
    UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(ib);

    Rules::BreakpointSet bs;

    bs.breakpoint_number = ub.number;
    bs.address = { "00000000" };
    bs.file_name = stbk.file_name;
    bs.line_number = stbk.line_number;

    GdbResponse resp;
    resp.prompt = gdb_prompt;
    resp.pushActionable(bs);
    toUser(resp);
}

Rules::BreakpointSet BreakpointManager::setGdbBreakpoint(Rules::SetBreakpoint const& stbk)
{
    channels.toGdb.WriteData(stbk);

    GdbResponse resp = channels.fromGdb.ReadData();

    if (auto* bs = getActionable<Rules::BreakpointSet>(&resp.values.at(0)))
    {
        return *bs;
    }
    else
    {
        raiseError(BadResponseError("Did not get expected gdb response type from gdb when calling set breakpoint."));
    }

    // Never get here
    return Rules::BreakpointSet();
}

void BreakpointManager::userSetGdbBreakpoint(Rules::SetBreakpoint const& stbk)
{
    Rules::BreakpointSet bs = setGdbBreakpoint(stbk);

    GdbBreakpoint gb = { bs.breakpoint_number };
    UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(gb);

    bs.breakpoint_number = ub.number;

    GdbResponse resp;
    resp.prompt = gdb_prompt;
    resp.pushActionable(bs);
    toUser(resp);
}

// I wrote this function for getting the args using info args,
// but then realized I already could get the args from the BreakpointHit struct.
BreakpointManager::FunctionArgs BreakpointManager::getArgs()
{
    toGdb( Rules::Info { "args" } );
    GdbResponse resp = channels.fromGdb.ReadData();

    BreakpointManager::FunctionArgs result;

    for (auto item : resp.values)
    {
        if (auto* locals = getActionable<Rules::LocalsInfo>(&item))
        {
            if (auto* nl = boost::get<Rules::NoLocals>(&(locals->value)))
                result.push_back( std::make_pair(nl->text, Rules::GdbValue()) );
            else if (auto* veq = boost::get<Rules::VariableEquals>(&(locals->value)))
                result.push_back({ veq->name, veq->value });
            else
                raiseError(BadResponseError("Did not get expected LocalsInfo line from gdb when calling info locals."));
        }
        else
            raiseError(BadResponseError("Did not get expected gdb response type from gdb when calling info locals."));
    }

    return result;
}

BreakpointManager::FunctionArgs BreakpointManager::getArgs(Rules::GdbResponseFunction func)
{
    BreakpointManager::FunctionArgs result;

    for (auto arg : func.args)
    {
        result.push_back({ arg.name, arg.value });
    }

    return result;
}

Rules::GdbValue BreakpointManager::getArg(BreakpointManager::FunctionArgs args, std::string arg_name)
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

Rules::GdbAddress BreakpointManager::getPointer(BreakpointManager::FunctionArgs args, std::string arg_name)
{
    auto value = getArg(args, arg_name);

    if (auto* result = boost::get<Rules::GdbAddress>(&(value.value)))
        return *result;
    else
        raiseError(BadResponseError("Did not get expected LocalsInfo variable type for arg " + arg_name + " from gdb when calling info locals."));

    // Never get here
    return Rules::GdbAddress();
}

void BreakpointManager::ioDebuggerInit(const Rules::BreakpointHit& bh)
{
    // At inferior function "io_debugger_init"

    auto args = getArgs(bh.function);
    Rules::GdbAddress io_state = getPointer(args, "io_state");

    for (IoBreakpoint ib : deferred_breakpoints)
    {
        loadDeferredBreakpoint(io_state, ib);
    }

    // Give the user the illusion the breakpoint was never hit.
    toGdb( Rules::StepMode {"cont"} );
}

GdbActionable BreakpointManager::ioDebuggerIoBreakpoint(const Rules::BreakpointHit& bh)
{
    // At inferior function "io_debugger_break_here"

    auto args = getArgs(bh.function);
    auto self = getPointer(args, "self");
    auto locals = getPointer(args, "locals");
    auto m = getPointer(args, "m");
    int breakpoint_number = getInt(args, "breakpoint_number");
    std::string file_name = getValueAsString(args, "file_name");
    int line_number = getInt(args, "line_number");

    fs::path p(file_name);
    //fs::path full_p = fs::complete(p); // complete == absolute
    fs::path full_p = fs::absolute(p);

    ScriptContext context = { self, locals, m };
    watch_mgr.setScriptContext(context);

    Rules::BreakpointHit bh_spoof;
    bh_spoof.breakpoint_number = breakpoint_number;
    // bh_spoof.function = {}; TODO:  Get message name and argument names.
    bh_spoof.file_name = full_p.string();
    bh_spoof.line_number = line_number;

    Rules::CursorPos cp_spoof;
    cp_spoof.file_name = full_p.string();
    cp_spoof.line_number = line_number;
    cp_spoof.char_number = 1;
    cp_spoof.unknown = "beg";
    cp_spoof.address = { "00000000" };

    GdbResponse resp_spoof;
    resp_spoof.prompt = gdb_prompt;
    resp_spoof.pushActionable(Rules::Empty());
    resp_spoof.pushActionable(bh_spoof);
    resp_spoof.pushActionable(cp_spoof);

    channels.toUser.WriteData(resp_spoof);

    return {Rules::Empty()};
}

bool BreakpointManager::isIoBreakpoint(string file_name) const
{
    return
        boost::algorithm::ends_with(file_name, ".io") ||
        boost::algorithm::ends_with(file_name, "io.inl");
}

void BreakpointManager::userSetBreakpoint(const Rules::SetBreakpoint& t)
{
    if (isIoBreakpoint(t.file_name))
        userSetIoBreakpoint(t);
    else
        userSetGdbBreakpoint(t);
}

GdbActionable BreakpointManager::gdbBreakpointSet(const Rules::BreakpointSet& t)
{
    Rules::BreakpointSet bs(t);
    GdbBreakpoint gb = {t.breakpoint_number};
    bs.breakpoint_number = brkpts.get_user_breakpoint<UserBreakpoint>(gb).number;
    return {bs};
}

GdbActionable BreakpointManager::gdbBreakpointPending(const Rules::BreakpointPending& t)
{
    Rules::BreakpointPending bp(t);
    GdbBreakpoint gb = {t.breakpoint_number};
    bp.breakpoint_number = brkpts.get_user_breakpoint<UserBreakpoint>(gb).number;
    return {bp};
}

GdbActionable BreakpointManager::gdbBreakpointHit(const Rules::BreakpointHit& t, bool& is_our_breakpoint)
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
            return {Rules::Empty()};
        }
        else if (ob == *io_debugger_breakpoint)
        {
            return ioDebuggerIoBreakpoint(t);
        }
        else
        {
            raiseError(LogicError("Hit one of 'our' internal debugger breakpoints, but it does not match the ones we set."));
            return {Rules::Empty()};
        }
    }
    else
    {
        Rules::BreakpointHit bh(t);
        bh.breakpoint_number = brkpts.get_user_breakpoint<UserBreakpoint>(gb).number;
        return {bh};
    }
}

GdbActionable BreakpointManager::gdbCursorPos(const Rules::CursorPos& t, bool hit_our_breakpoint)
{
    // Suppress returning the cursor position if the breakpoint is one of ours.
    if (hit_our_breakpoint)
        return {Rules::Empty()};
    else
        return {t};
}

