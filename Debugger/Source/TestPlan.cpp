#include "TestPlan.hpp"
using namespace std;
using namespace Iocaste::Debugger;

TestActionType TestPlan::actionType(ActivityLogLine entry) const
{
    return label_actions[entry.label];
}

void TestPlan::setAction(std::string label, TestActionType action)
{
    label_actions[label] = action;
}
