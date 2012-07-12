#define BOOST_FILESYSTEM_VERSION 2
#include <boost/process.hpp>

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
namespace bp = ::boost::process;

//#include "Worker.hpp"
//#include "CharInput.hpp"
//#include "LineInput.hpp"
//#include "StreamOutput.hpp"
//#include "Queue.hpp"
//#include "LookForPrompt.hpp"
//#include "Parser.hpp"
//#include "ActivityLog.hpp"
//#include "Channel.hpp"

//using namespace Iocaste::Debugger;

enum class MainLoopState
{
    ReadUser,
    WriteGdb,
    ReadGdb,
    WriteUser,
    Quit
};

/*
void main_loop(Channel<UserCmd, GdbResponse> gdb, Channel<GdbResponse, UserCmd> user)
{
    // Relay gdb's welcome message before processing user commands.  Codeblocks seems to require this.
    user.to.WriteData(gdb.from.ReadData());

    MainLoopState state = MainLoopState.ReadUser;
    UserCmd cmd;
    GdbResponse response;

    while (true)
    {
        switch (state)
        {
            case MainLoopState.ReadUser:
                cmd = user.from.ReadData();
                state = processCmd(cmd, gdb, user);
                break;

            case MainLoopState.WriteGdb:
                gdb.to.WriteData(cmd)
                state = MainLoopState.ReadGdb;
                break;

            case MainLoopState.ReadGdb:
                response = gdb.from.ReadData();
                state = processResponse(response, gdb, user);
                break;

            case MainLoopState.WriteUser:
                user.to.WriteData(response);
                state = MainLoopState.ReadUser;
                break;

            case MainLoopState.Quit:
                return;
        }
    }
}
*/

bp::child start_gdb(int argc, char* argv[])
{
    std::vector<std::string> args;
    args.push_back("/usr/bin/gdb");

    for (int i=1; i<argc; ++i)
        args.push_back(argv[i]);

    std::string exec = args[0];

    bp::context ctx;
    ctx.stdout_behavior = bp::capture_stream();
    ctx.stdin_behavior = bp::capture_stream();

    return bp::launch(exec, args, ctx);
}

#include "LikeMagic/Utility/IndexPack.hpp"
using LikeMagic::Utility::IndexPack;
using LikeMagic::Utility::MakeIndexPack;

struct UnusedType {};

struct ChainPolicy
{
    struct None {};
    struct RHS {};
    struct Both {};
};

template <typename T>
UnusedType get(ChainPolicy, T const&)
{
    static_assert(sizeof(T) && 0, "No chaining policy defined for this type.");
    throw nullptr;
}

template <typename T, typename LHS, typename RHS, typename Policy>
struct ChainBuilder
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
        { static_assert(sizeof(T) && false, "Unrecognized Chaining policy."); throw 0; }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS, ChainPolicy::None>
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
        { return new T(std::get<Indices>(args)...); }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS, ChainPolicy::RHS>
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
        { return new T(rhs, std::get<Indices>(args)...); }
};

template <typename T, typename LHS, typename RHS>
struct ChainBuilder<T, LHS, RHS, ChainPolicy::Both>
{
    template <typename... Args, int... Indices>
    static T* create(LHS lhs, RHS rhs, std::tuple<Args...> args, IndexPack<Indices...> ipack)
        { return new T(*lhs.force().second, rhs, std::get<Indices>(args)...); }
};

template <typename RHS>
struct StopUnwind
{
    RHS& _unwind(RHS& rhs) { return rhs; }
};

template <typename T, typename LeftFuture, typename HeadType, typename... Args>
struct Future
{
    T* self;
    LeftFuture& lhs;
    std::tuple<Args...> args;

    Future(LeftFuture& lhs_, std::tuple<Args...> args_)
        : self(nullptr), lhs(lhs_), args(args_) { }

    std::pair<HeadType*, T*> force()
    {
        HeadType& head = _unwind(UnusedType());
        T& temp = *self;
        return std::make_pair(&head, &temp);
    }

    template <typename RHS>
    HeadType& _unwind(RHS rhs)
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

        if (!self)
            self = ChainBuilder<T, decltype(lhs), decltype(rhs),
                decltype(get(ChainPolicy(), *(T*)0))>::create(lhs, rhs, args, IPack());

        return lhs._unwind(*self);
    }

    template <typename Next, typename... NextArgs>
    Future<Next, Future, HeadType, NextArgs...> to(NextArgs... args_)
    {
        return Future<Next, Future, HeadType, NextArgs...>(*this, std::make_tuple(args_...));
    }
};

struct Chain
{
    template <typename T, typename... NextArgs>
    Future<T, StopUnwind<T>, T, NextArgs...> to(NextArgs... args_)
    {
        StopUnwind<T>& lhs = *new StopUnwind<T>();
        return Future<T, StopUnwind<T>, T, NextArgs...>(lhs, std::make_tuple(args_...));
    }
};

int global_counter = 0;

struct HasId
{
private:
    int id;
protected:
    HasId() : id(++global_counter) {}
public:
    int GetId() const { return id; }
};

struct IInput : public virtual HasId { };
struct IOutput : public virtual HasId { };

struct Input : public IInput
{
    Input()
    {
        cout << " Input " << GetId() << " created " << endl;
    }
};

struct Output : public IOutput
{
    //typedef ChainPolicy::None policy;

    Output()
    {
        cout << " Output " << GetId() << " created " << endl;
    }
};

struct Adapter : public IOutput
{
    typedef ChainPolicy::RHS policy;

    Adapter(IOutput& rhs)
    {
        cout << " Adapter " << GetId() << " created over(" << rhs.GetId() << ") " << endl;
    }
};

struct TestWorker : private HasId
{
    typedef ChainPolicy::Both policy;
    std::string name;

    TestWorker(IInput& lhs, IOutput& rhs, std::string name_)
        : name(name_)
    {
        cout << " Worker " << GetId() << "'" << name << "'" << " created over(" << lhs.GetId() << "," << rhs.GetId() << ") " << endl;
    }
};

struct TestQueue : public IInput, public IOutput
{
    typedef ChainPolicy::None policy;

    TestQueue()
    {
        cout << " Queue " << GetId() << " created " << endl;
    }
};

// You define chaining policies for various base types by overloading the "get(ChainPolicy,x)" function.
// You don't need to define these functions; the declaration of the return type is enough.
// The reason overloading is a useful mechanism for doing this is that it has two useful features:
//  1. If derived <: base, then derived will "inherit" base's policies too
//  2. Unless you defined a policy for derived, in which case overload resolution rules will match "derived", which is what you want.
//  3. The declaration that associates a policy with a class can be separate from both the class and the user, kind of like a Concept.
// Keep in mind that a class may have many types of policies associated with it in different contexts,
// and policies may be defined for classes we don't have the freedom to change, like library or framework classes.
// Google Andrei Alexandrescu for more info on Policy based programming.
ChainPolicy::None get(ChainPolicy, Input const&);
ChainPolicy::None get(ChainPolicy, Output const&);
ChainPolicy::RHS  get(ChainPolicy, Adapter const&);
ChainPolicy::Both get(ChainPolicy, TestWorker const&);
ChainPolicy::None get(ChainPolicy, TestQueue const&);

int main(int argc, char* argv[])
{
    Chain().to<Input>().to<TestWorker>("first").to<TestQueue>().to<TestWorker>("second").to<Adapter>().to<Output>().force();
    return 0;
    /*

    std::ofstream log_file("/Users/dennisferron/debug.log", ofstream::out);
    StreamOutput debug_log(log_file, true);
    ActivityLog activity_log(debug_log);

    bp::child c = start_gdb(argc, argv);

    bp::postream& os = c.get_stdin();
    bp::pistream& is = c.get_stdout();

    CharInput raw_gdb_chars(is);
    StreamOutput to_gdb(os);

    AbstractOutput<string>& log_to_gdb = activity_log.Wrap("toGdb", to_gdb);

    Queue<string> gdb_response_queue;

    AbstractOutput<string>& log_gdb = activity_log.Wrap("fromGdb", gdb_response_queue);

    LookForPrompt look_for_prompt(log_gdb, "(gdb) ");
    Worker gdb_reader(raw_gdb_chars, look_for_prompt, "from gdb look for prompt", debug_log);

    LineInput raw_from_user(std::cin);
    StreamOutput raw_to_user(std::cout);

    AbstractOutput<string>& log_to_user = activity_log.Wrap("toUser", raw_to_user);

    Queue<UserCmd> user_cmd_queue;

    UserCmdParser cmd_parser(user_cmd_queue);

    AbstractOutput<string>& log_from_user = activity_log.Wrap("fromUser", cmd_parser);

    Worker user_reader(raw_from_user, log_from_user);

    bp::status s = c.wait();

    std::cerr << "exited = " << s.exited() << " exit_status = " << s.exit_status() << std::endl;

    return 0;
    */
}

