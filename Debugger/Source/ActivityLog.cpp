#include <iostream>
#include <string>
#include <complex>
using namespace std;

#include "ActivityLog.hpp"
#include "ActivityLogLine.hpp"
#include "TestPlan.hpp"
#include "Exception.hpp"
#include "LogChannel.hpp"
using namespace Iocaste::Debugger;

namespace Iocaste {
    namespace Debugger {

AbstractOutput<std::string>& no_call_copy_constructor(ActivityLog& value)
{
    return static_cast<AbstractOutput<std::string>&>(value);
}

ActivityLog::ActivityLog(AbstractOutput<std::string>& log_file_, TestPlan& plan_)
    : log_file(log_file_), test_plan(plan_)
{
}

// channels write data to log
void ActivityLog::WriteData(ActivityLogLine const& entry)
{
    pthread_mutex_lock(&record_mutex);

    // Putting this inside the locks complies with queue's documented semantics of
    // "valid for one producer and one consumer thread".  But maybe it is actually ok to push to it from multiple threads?
    test_results.WriteData(entry);

    std::string output;
    entry.Write(output);
    log_file.WriteData(output);

    pthread_mutex_unlock(&record_mutex);
}

// Write log file line back onto outputs.
void ActivityLog::WriteData(std::string const& data)
{
    ActivityLogLine entry;
    entry.Parse(data);

    switch (test_plan.actionType(entry))
    {
        case TestActionType::ignore:
            break;
        case TestActionType::write:
            if (channels.find(entry.label) != channels.end())
                channels[entry.label]->WriteData(entry);
            else
                pending[entry.label].WriteData(entry);
            break;
        case TestActionType::expectAny:
            expect(entry, false);
            break;
        case TestActionType::expectExact:
            expect(entry, true);
            break;
    }
}

void ActivityLog::expect(ActivityLogLine test_log_entry, bool exact_match)
{
    ActivityLogLine test_result;

    // Get the next result that is not part of the ignored labels.
    do { test_result = test_results.ReadData(); }
    while (test_plan.actionType(test_result) == TestActionType::ignore);

    if (test_result.label != test_log_entry.label)
        throw TestException("Did not get expected label", test_log_entry.label, test_result.label);
    else if (exact_match && test_result.content != test_log_entry.content)
        throw TestException("Did not get expected content", test_log_entry.content, test_result.content);
}


void ActivityLog::AddChannel(std::string label, LogChannel& channel)
{
    channels[label] = &channel;

    if (pending.find(label) != pending.end())
    {
        while (pending[label].HasData())
            channel.WriteData(pending[label].ReadData());
    }
}

    }
}

