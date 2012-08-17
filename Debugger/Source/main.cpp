
#include "boost/assert.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <functional>
using namespace std;

#include "InputChain.hpp"
#include "InputChainComponents.hpp"
#include "TestPlan.hpp"
#include "Configuration.hpp"
#include "UserCmdHandler.hpp"
#include "GdbResponseHandler.hpp"
using namespace Iocaste::Debugger;


void checkErrors(MainChannels channels)
{
    try
    {
        if (channels.errors.HasData())
        {
            auto e = channels.errors.ReadData();
            boost::rethrow_exception(e);
        }
    }
    catch (TestException const& e)
    {
        cerr << endl << "Test failed " << e.what() << endl;
    }
    catch (Exception const& e)
    {
        cerr << endl << e.what() << endl;
    }
//    catch (std::exception const& e)
//    {
//        cerr << e.what() << endl;
//    }
    catch (...)
    {
        cerr << "unknown err" << endl;
    }
}


/*

Execution diagram

    main loop           user cmd handler

    +---+          +-------+              +-------+
    |   |          |       v              |       |
    |   |          |  GDB will handle?    |       v
    |   v          |  Yes  No------->handle   write GDB
    |   user cmd?  |   v             cmd  ^     read GDB
    |   No Yes->read   write         |    +-------+
    |   |       user   GDB           v
    |   v              v         fake response
    |   gdb resp?<-----+<--------write to user
    +-<--No  Yes
    ^         |
    |         v
    |     gdb response
    |     write to user
    |         |
    +<--------+

It is not as crazy as it looks.

There are just a few basic ideas at work in the diagram:

UserCmd handler

    Whenever a UserCmd is received, the user command handler
    either writes it to gdb or handles it internally.

    In the process of handling a command itself, the handler may write
    other commands to gdb and read those responses.

    After handling a command internally, the command
    handler always writes some (faked) response.

Main Loop

    The main loop is agnostic as to whether the next
    input should be from the user first or gdb first.

        This prevents the debugger from becoming unresponsive
        while waiting on the wrong input source.
*/


void mainLoop(MainChannels channels)
{
    BreakpointMap brkpts;
    UserCmdHandler cmd_handler(channels, brkpts);
    GdbResponseHandler resp_handler(channels, brkpts);

    while (true)
    {
        checkErrors(channels);

        if (channels.fromUser.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadUser");
            UserCmd cmd = channels.fromUser.ReadData();
            cmd_handler.handle(cmd);
        }

        checkErrors(channels);

        if (channels.fromGdb.HasData())
        {
            channels.info.WriteData("MainLoopState::ReadGdb");
            GdbResponse response = channels.fromGdb.ReadData();
            resp_handler.handle(response);
        }
    }
}


int main(int argc, char* argv[])
{
    boost::shared_ptr<Configuration> config = getConfiguration(argc, argv);

    Queue<boost::exception_ptr> error_queue;
    Queue<std::string> end_marker_queue;

    // I could have put the test plan into the configuration object,
    // but it doens't really hurt anything to have the test plan here
    // every time even when it's not used.
    TestPlan plan1;
    plan1.setAction("info", TestActionType::ignore);
    plan1.setAction("fromUser", TestActionType::write);
    plan1.setAction("toGdb", TestActionType::expectExact);
    plan1.setAction("fromGdb", TestActionType::write);
    plan1.setAction("toUser", TestActionType::expectExact);
    // ignore exceptions from code under test to prevent generating additional "did not get expected label" exceptions.
    plan1.setAction("exception", TestActionType::ignore);

    auto log_replay = InputChain().to<LineInput>(config->get_from_log()).to<Worker>("log_replay", error_queue)
        .to<ActivityLog>(plan1).to<StreamOutput>(config->get_to_log(), true).complete();

    auto& log = log_replay.at<ActivityLog>(0);

    auto exception_log = InputChain().to<LogChannel>(log, "exception").to<StreamOutput>(cerr).complete();
    setExceptionLog(&exception_log.at<LogChannel>(0));

    auto fromUser = InputChain().to<LineInput>(config->get_from_user()).to<Worker>("fromUser", error_queue)
        .to<LogChannel>(log, "fromUser").to<UserCmdParser>().to<Queue<UserCmd>>().complete();

    // LineInput eats newlines so fromUser -> toGdb stream output must re-add newline (pass true to stream output).
    auto toGdb = InputChain().to<UserCmdWriter>().to<LogChannel>(log, "toGdb")
        .to<StreamOutput>(config->get_to_gdb(), true).complete();

    string prompt = "(gdb) ";
    auto fromGdb = InputChain().to<CharInput>(config->get_from_gdb()).to<Worker>("fromGdb", error_queue)
        .to<LookForPrompt>(end_marker_queue).to<LogChannelWithPrompt>(log, "fromGdb")
        .to<GdbResponseParser>().to<Queue<GdbResponse>>().complete();

    // CharInput does not eat newlines, and look-for-prompt looks for a prompt string not a newline, so newlines are NOT eaten
    // therefore fromGdb -> toUser does not need to re-add a newline.
    auto toUser = InputChain().to<GdbResponseWriter>().to<LogChannelWithPrompt>(log, "toUser").to<RecombinePrompt>()
        .to<StreamOutput>(config->get_to_user(), false).complete();

    auto errChannel = InputChain().to<LineInput>(config->get_from_gdb_err()).to<Worker>("fromGdbErr", error_queue)
        .to<LogChannel>(log, "fromGdbErr").to<StreamOutput>(config->get_to_user_err(), true).complete();

    auto info = InputChain().to<LogChannel>(log, "info").to<StreamOutput>(cerr, true).complete();

    info.head().WriteData("Built input chains.");

    mainLoop(MainChannels(fromUser.tail(), toUser.head(), fromGdb.tail(), toGdb.head(), info.head(), error_queue, end_marker_queue));

    // This doesn't do much good if they are blocked waiting on stream input.
    fromUser.at<Worker>(0).stop_thread_soon();
    fromGdb.at<Worker>(0).stop_thread_soon();
    log_replay.at<Worker>(0).stop_thread_soon();

    return 0;
}

