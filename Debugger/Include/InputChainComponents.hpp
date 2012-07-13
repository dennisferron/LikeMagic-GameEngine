#pragma once

#include "ChainPolicy.hpp"
// include other components

// testing
namespace Iocaste {
    namespace Debugger {

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

}}

namespace Iocaste {
    namespace Debugger {

ChainPolicy::None get(ChainPolicy, Input const&);
ChainPolicy::None get(ChainPolicy, Output const&);
ChainPolicy::RHS  get(ChainPolicy, Adapter const&);
ChainPolicy::Both get(ChainPolicy, TestWorker const&);
ChainPolicy::None get(ChainPolicy, TestQueue const&);

    }
}
