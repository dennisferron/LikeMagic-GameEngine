
#include "WatchManager.hpp"
#include "Exception.hpp"

namespace Iocaste { namespace Debugger {

WatchManager::WatchManager(MainChannels const& channels_, GdbResponseParser& resp_parser_)
    : channels(channels_), at_script_breakpoint(false), has_script_context(false), resp_parser(resp_parser_)
{
}

void WatchManager::atScriptBreakpoint(bool value)
{
    at_script_breakpoint = value;
}

void WatchManager::setScriptContext(ScriptContext context_)
{
    channels.info.WriteData("Set script context");
    has_script_context = true;
    context = context_;
}

void WatchManager::respActionable(GdbActionableType msg)
{
    GdbResponse resp;

    resp.values.push_back(
        GdbActionable { msg }
    );

    channels.toUser.WriteData(resp);
}

void WatchManager::respContextSens(GdbContextSensitiveType msg)
{
    GdbResponse resp;

    resp.values.push_back(
        GdbContextSensitive { msg }
    );

    channels.toUser.WriteData(resp);
}

void WatchManager::respUnactionable(GdbUnactionableType msg)
{
    GdbResponse resp;

    resp.values.push_back(
        GdbUnactionable { msg }
    );

    channels.toUser.WriteData(resp);
}

void WatchManager::handle(UserCmds::Info const& cmd)
{
    if (at_script_breakpoint && has_script_context && cmd.value == "locals")
    {
        respActionable(GdbResponses::LocalsInfo { SharedTypes::NoLocals {"No locals."} });
    }
    else if (at_script_breakpoint && has_script_context && cmd.value == "args")
    {
        respActionable(GdbResponses::LocalsInfo { SharedTypes::NoLocals {"No arguments."} });
    }
    else
    {
        channels.toGdb.WriteData(cmd);
    }
}

void WatchManager::handle(UserCmds::WhatIs const& cmd)
{
    if (at_script_breakpoint && has_script_context && cmd.cmd == "whatis")
    {
        GdbResponses::TypeEquals te;
        te.type = "IoObject";
        respActionable(te);
    }
    else if (at_script_breakpoint && has_script_context && cmd.cmd == "output")
    {
        UserCmds::PrintFunction print;
        print.function_name = "io_debugger_watch_type";
        print.args.push_back( { context.locals } );
        print.args.push_back( { *(cmd.expr) } );
        channels.toGdb.WriteData(print);

        GdbResponse resp = channels.fromGdb.ReadData();

        if (auto* vh = getActionable<GdbResponses::ValueHistory>(&resp.values.at(0)))
        {
            if (vh->value.value_as_string)
            {
                GdbResponses::RawStr rs;
                rs.value = vh->value.value_as_string->text;
                respUnactionable(rs);
            }
            else
            {
                raiseError(BadResponseError("Did not get expected function return type from gdb when calling io_debugger_watch_type."));
            }
        }
        else
        {
            raiseError(BadResponseError("Did not get expected gdb response type from gdb when calling io_debugger_watch_type."));
        }
    }
    else
    {
        if (cmd.cmd == std::string("output"))
            resp_parser.expectAltInput();

        channels.toGdb.WriteData(cmd);
    }
}


}}

