#pragma once

#include "MainChannels.hpp"
#include "SharedTypes.hpp"
#include "GdbResponseParser.hpp"

#include <vector>

namespace IoDbg {

struct ScriptContext
{
    Rules::GdbAddress self;
    Rules::GdbAddress locals;
    Rules::GdbAddress m;
};

class WatchManager
{
private:

    MainChannels channels;
    bool at_script_breakpoint;
    bool has_script_context;
    ScriptContext context;
    std::string gdb_prompt;
    GdbResponseParser& resp_parser;

    void respActionable(GdbActionableType msg);
    void respUnactionable(GdbUnactionableType msg);
    void respContextSens(GdbContextSensitiveType msg);

public:

    WatchManager(MainChannels const& channels_, GdbResponseParser& resp_parser_);
    void setPrompt(std::string new_prompt);
    void setScriptContext(ScriptContext context);
    void atScriptBreakpoint(bool value);
    void handle(Rules::Info const& cmd);
    void handle(Rules::WhatIs const& cmd);
};

}

