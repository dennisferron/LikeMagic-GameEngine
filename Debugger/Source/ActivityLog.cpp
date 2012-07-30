#include <iostream>
#include <string>
#include <complex>
#include <algorithm>
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
    boost::mutex::scoped_lock lock(record_mutex);
    test_results.WriteData(entry);
    std::string output;
    entry.Write(output);
    log_file.WriteData(output);
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

void print_error(string expected, string actual)
{
    int expected_lines = std::count(expected.begin(), expected.end(), '\n');
    int actual_lines = std::count(actual.begin(), actual.end(), '\n');

    cerr << endl << "Did not get expected content" << endl << "expected (" << expected_lines << " lines): ->" << expected << "<-" << endl
    << "actual (" << actual_lines << " lines):  ->" << actual << "<-" << endl;
    cerr << endl;
}

void ActivityLog::expect(ActivityLogLine test_log_entry, bool exact_match)
{
    ActivityLogLine test_result;

    // Get the next result that is not part of the ignored labels.
    do      { test_result = test_results.ReadData(); }
    while   (test_plan.actionType(test_result) == TestActionType::ignore);

    if (test_result.label != test_log_entry.label)
        throw boost::enable_current_exception(TestException("Did not get expected label", test_log_entry.label, test_result.label));
    else if (exact_match && test_result.content != test_log_entry.content)
    {
        string expected = test_log_entry.content;
        string actual = test_result.content;

        print_error(expected, actual);

        throw boost::enable_current_exception(TestException("Did not get expected content", expected, actual));
    }
}


void ActivityLog::AddChannel(std::string label, AbstractOutput<ActivityLogLine>& channel)
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

