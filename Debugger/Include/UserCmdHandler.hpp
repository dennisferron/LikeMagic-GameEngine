#include "MainChannels.hpp"
#include "BreakpointMap.hpp"

namespace Iocaste { namespace Debugger {

class UserCmdHandler
{
private:
    MainChannels channels;
    BreakpointMap& brkpts;
    std::string last_prompt;
    boost::optional<OurBreakpoint> io_debugger_breakpoint;
    boost::optional<OurBreakpoint> io_init_breakpoint;
    std::vector<IoBreakpoint> deferred_breakpoints;

    struct Visitor;
    friend struct Visitor;
    struct Visitor : boost::static_visitor<>
    {
        UserCmdHandler& handler;

        Visitor(UserCmdHandler& handler_) : handler(handler_) {}

        template <typename T>
        void operator()(const T& t) const
        {
            handler.toGdb(t);
        }

        void operator()(const UserCmds::SetOption& t) const
        {
            if (t.name == "prompt")
                handler.channels.end_markers.WriteData(handler.last_prompt = t.value);

            handler.toGdb(t);
        }

        void operator()(const UserCmds::SetBreakpoint& t) const
        {
            if (boost::algorithm::ends_with(t.file_name, ".io"))
                handler.handleIoBreakpoint(t);
            else
                handler.handleGdbBreakpoint(t);
        }
    };

    void toGdb(UserCmd const& cmd) const
    {
        channels.toGdb.WriteData(cmd);
    }

    void toUser(GdbResponse const& response) const
    {
        channels.toUser.WriteData(response);
    }

    OurBreakpoint setIoDebuggerBreakpoint(std::string function_name) const
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
            // Todo: this is not necessarily a logic error in this program per se,
            // need an exception type for "did not get expected response".
            raiseError(LogicError("Did not get expected gdb response type from gdb when setting breakpoint on " + function_name + "() function."));

            // never get here
            return {-1};
        }
    }

    void loadDeferredBreakpoint(SharedTypes::GdbAddress io_state, IoBreakpoint ib)
    {
        UserCmds::PrintFunction print;
        print.function_name = "io_debugger_set_breakpoint";
        print.args.push_back( { io_state } );
        print.args.push_back( { ib.breakpoint_number } );
        print.args.push_back( { ib.file_name } );
        print.args.push_back( { ib.line_number } );
        channels.toGdb.WriteData(print);

        GdbResponse resp = channels.fromGdb.ReadData();

        if (auto* vh = boost::get<GdbResponses::ValueHistory>(&resp.values.at(0)))
        {
            if (auto* breakpt_num = boost::get<int>(&(vh->value.value)))
            {
                return {*breakpt_num};
            }
            else
            {
                raiseError(LogicError("Did not get expected function return type from gdb when calling io_debugger_set_breakpoint."));
            }
        }
        else
        {
            // Todo: this is not necessarily a logic error in this program per se,
            // need an exception type for "did not get expected response".
            raiseError(LogicError("Did not get expected gdb response type from gdb when calling io_debugger_set_breakpoint."));
        }
    }

    IoBreakpoint setIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
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
    }

    void handleIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        IoBreakpoint ib = setIoBreakpoint(stbk);
        UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(ib);

        GdbResponses::BreakpointSet bs;

        bs.breakpoint_number = ub.number;
        bs.address = { "0x00000000" };
        bs.file_name = stbk.file_name;
        bs.line_number = stbk.line_number;

        GdbResponse resp;
        resp.prompt = last_prompt;
        resp.values.push_back(bs);
        toUser(resp);
    }

    GdbResponses::BreakpointSet setGdbBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        channels.toGdb.WriteData(stbk);

        GdbResponse resp = channels.fromGdb.ReadData();

        if (auto* bs = boost::get<GdbResponses::BreakpointSet>(&resp.values.at(0)))
        {
            return *bs;
        }
        else
        {
            // Todo: this is not necessarily a logic error in this program per se,
            // need an exception type for "did not get expected response".
            raiseError(LogicError("Did not get expected gdb response type from gdb when calling set breakpoint."));
        }

        // Never get here
        return GdbResponses::BreakpointSet();
    }

    void handleGdbBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        GdbResponses::BreakpointSet bs = setGdbBreakpoint(stbk);

        GdbBreakpoint gb = { bs.breakpoint_number };
        UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(gb);

        bs.breakpoint_number = ub.number;

        GdbResponse resp;
        resp.prompt = last_prompt;
        resp.values.push_back(bs);
        toUser(resp);
    }

public:

    UserCmdHandler(MainChannels const& channels_, BreakpointMap& brkpts_)
        : channels(channels_), brkpts(brkpts_) {}

    void handle(UserCmd const& cmd)
    {
        boost::apply_visitor(Visitor(*this), cmd);
    }

    void ioDebuggerInit(SharedTypes::GdbAddress io_state)
    {
        for (IoBreakpoint ib : deferred_breakpoints)
        {
            loadDeferredBreakpoint(io_state, ib);
        }
    }
};

}}
