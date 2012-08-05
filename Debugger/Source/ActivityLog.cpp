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

void print_diff(string expected, string actual)
{
    if (expected.size() != actual.size())
        cerr << "The strings are not the same length, expected "
            << expected.size() << " actual " << actual.size() << endl;

    for (size_t i=0; i < expected.size() || i < actual.size(); ++i)
    {
        if (i < expected.size() && i < actual.size())
        {
            if (expected[i] != actual[i])
            {
                cerr << "At index " << i
                    << " expected char "
                        << (int)expected[i] << "'" << expected[i] << "'"
                    << " got "
                        << (int)actual[i] << "'" << actual[i] << "'"
                    << endl;
            }
        }
        else if (i < expected.size())
        {
            cerr << "At index " << i << " expected char " << (int)expected[i] << " got end of string" << endl;
        }
        else
        {
            cerr << "At index " << i << " expected end of string got char " << (int)actual[i] << endl;
        }
    }
}

void print_error(string expected, string actual)
{
    int expected_lines = std::count(expected.begin(), expected.end(), '\n');
    int actual_lines = std::count(actual.begin(), actual.end(), '\n');

    cerr << endl << "Did not get expected content" << endl << "expected (" << expected_lines << " lines): ->" << expected << "<-" << endl
    << "actual (" << actual_lines << " lines):   ->" << actual << "<-" << endl;
    cerr << endl;

    print_diff(expected, actual);
}

void ActivityLog::expect(ActivityLogLine test_log_entry, bool exact_match)
{
    string expected = test_log_entry.content;

    // Get the next result that is not part of the ignored labels.
    ActivityLogLine test_result;
    do
    {
        int counter = 0;
        while (!test_results.HasData())
        {
            boost::this_thread::sleep(boost::posix_time::milliseconds(5));
            if (++counter > 100)
            {
                //string msg = "Timed out waiting on next test result.";
                //string log_line = test_log_entry.label + ": " + expected;
                //cerr << msg << " expected " << log_line << endl;
                //throw boost::enable_current_exception(TestException(msg, log_line, ""));
            }
        }
        test_result = test_results.ReadData();
    }
    while   (test_plan.actionType(test_result) == TestActionType::ignore);

    if (test_result.label != test_log_entry.label)
    {
        cerr << "Did not get expected label, expected " << test_log_entry.label << " got " << test_result.label << endl;
        throw boost::enable_current_exception(TestException("Did not get expected label", test_log_entry.label, test_result.label));
    }
    else if (exact_match && test_result.content != test_log_entry.content)
    {
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

