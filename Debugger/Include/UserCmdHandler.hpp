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

    OurBreakpoint setIoDebuggerBreakHere() const
    {
        UserCmds::SetBreakpointOnFunction real_bkpt = { "io_debugger_break_here" };
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
            raiseError(LogicError("Did not get expected gdb response type from gdb when setting breakpoint on io_debugger_break_here() function."));

            // never get here
            return {-1};
        }
    }

    IoBreakpoint setIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        if (!io_debugger_breakpoint)
            io_debugger_breakpoint = setIoDebuggerBreakHere();

        UserCmds::PrintFunction print;
        print.function_name = "io_debugger_set_breakpoint";
        print.args.push_back(stbk.file_name);
        print.args.push_back(stbk.line_number);
        channels.toGdb.WriteData(print);

        GdbResponse resp = channels.fromGdb.ReadData();

        if (auto* vh = boost::get<GdbResponses::ValueHistory>(&resp.values.at(0)))
        {
            if (auto* breakpt_num = boost::get<int>(&vh->value))
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

        // Never get here
        return {-1};
    }

    void handleIoBreakpoint(UserCmds::SetBreakpoint const& stbk)
    {
        IoBreakpoint ib = setIoBreakpoint(stbk);
        UserBreakpoint ub = brkpts.get_user_breakpoint<UserBreakpoint>(ib);

        GdbResponses::BreakpointSet bs;

        bs.breakpoint_number = ub.number;
        bs.address = std::string("0x00000000");
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

};

}}
