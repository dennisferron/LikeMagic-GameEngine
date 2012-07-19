#include <iostream>
#include <string>
#include <complex>
using namespace std;

#include "ActivityLog.hpp"
#include "ActivityLogLine.hpp"
using namespace Iocaste::Debugger;

namespace Iocaste {
    namespace Debugger {

AbstractOutput<std::string>& no_call_copy_constructor(ActivityLog& value)
{
    return static_cast<AbstractOutput<std::string>&>(value);
}

ActivityLog::ActivityLog(AbstractOutput<std::string>& log_file_)
    : log_file(log_file_)
{
}

// channels write data to log
void ActivityLog::WriteData(ActivityLogLine const& entry)
{
    pthread_mutex_lock(&record_mutex);

    // Putting this inside the locks complies with queue's documented semantics of
    // "valid for one producer and one consumer thread".  But maybe it is actually ok to push to it from multiple threads?
    code_under_test.WriteData(entry);

    std::string output;
    entry.Write(output);
    log_file.WriteData(output);

    pthread_mutex_unlock(&record_mutex);
}

// Write actual log file line back onto outputs.
void ActivityLog::WriteData(std::string const& data)
{
    pthread_mutex_lock(&record_mutex);
    ActivityLogLine entry;
    entry.Parse(data);
    channels[entry.label]->WriteData(entry);
    pthread_mutex_unlock(&record_mutex);
}

void ActivityLog::expect(ActivityLogLine test_log_entry, bool exact_match)
{
    ActivityLogLine test_result;

    // Get the next result that is not part of the ignored labels.
    do { test_result = code_under_test.ReadData(); }
    while (test_plan.actionType(test_result) == TestActionType.ignore);

    if (test_result.label != test_log_entry.label)
        throw TestException("Did not get expected label");
    else if (exact_match && test_result.content != test_log_entry.content)
        throw TestException("Did not get expected content");
}

void ActivityLog::RunLoop()
{
    while (true)
    {
        ActivityLogLine test_log_entry = test_queue.ReadData();

        switch (test_plan.actionType(test_log_entry))
        {
            case TestActionType::ignore:
                break;
            case TestActionType::write:
                channels[test_log_entry.label]->WriteData(test_log_entry);
                break;
            case TestActionType::expectAny:
                expect(test_log_entry, false);
                break;
            case TestActionType::expectExact:
                expect(test_log_entry, true);
                break;
        }
    }
}



void ActivityLog::AddChannel(std::string label, AbstractOutput<ActivityLogLine>& channel)
{
    channels[label] = &channel;
}

    }
}

