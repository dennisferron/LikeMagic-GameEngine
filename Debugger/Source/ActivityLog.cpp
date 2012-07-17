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

void ActivityLog::WriteData(ActivityLogLine const& entry)
{
    pthread_mutex_lock(&record_mutex);
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

void ActivityLog::AddChannel(std::string label, AbstractOutput<ActivityLogLine>& channel)
{
    channels[label] = &channel;
}

    }
}

