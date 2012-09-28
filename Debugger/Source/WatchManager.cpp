
#include "WatchManager.hpp"

namespace Iocaste { namespace Debugger {

WatchManager::WatchManager(MainChannels const& channels_, GdbResponseParser& resp_parser_)
    : channels(channels_), at_script_breakpoint(false), resp_parser(resp_parser_)
{
}

void WatchManager::atScriptBreakpoint(bool value)
{
    at_script_breakpoint = value;
}

void WatchManager::setScriptContext(ScriptContext context_)
{
    context = context_;
}


void WatchManager::handle(UserCmds::Info const& cmd)
{
    if (at_script_breakpoint && cmd.value == "locals")
    {

    }
    else if (at_script_breakpoint && cmd.value == "args")
    {

    }
    else
    {
        channels.toGdb.WriteData(cmd);
    }
}

void WatchManager::handle(UserCmds::WhatIs const& cmd)
{
    if (at_script_breakpoint && cmd.cmd == "whatis")
    {
        GdbResponse resp;

        GdbResponses::TypeEquals te;
        te.type = "To be implemented";

        resp.values.push_back(
            GdbActionable {
                te
            }
        );

        channels.toUser.WriteData(resp);
    }
    else if (at_script_breakpoint && cmd.cmd == "output")
    {
        GdbResponse resp;

        resp.values.push_back(
            GdbContextSensitive {
                GdbResponses::OutputValue {
                    SharedTypes::GdbValue {
                        "Not implemented"
                    }
                }
            }
        );

        channels.toUser.WriteData(resp);
    }
    else
    {
        if (cmd.cmd == std::string("output"))
            resp_parser.expectAltInput();

        channels.toGdb.WriteData(cmd);
    }
}


}}

