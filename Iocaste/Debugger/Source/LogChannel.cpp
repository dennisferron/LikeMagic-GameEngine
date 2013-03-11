#include <iostream>
#include <string>
#include <complex>
using namespace std;

#include "ActivityLog.hpp"
#include "LogChannel.hpp"
#include "ActivityLogLine.hpp"
using namespace Iocaste::Debugger;


namespace Iocaste {
    namespace Debugger {

AbstractOutput<std::string>& no_call_copy_constructor(LogChannel& value)
{
    return static_cast<AbstractOutput<std::string>&>(value);
}


LogChannel::LogChannel(
  AbstractOutput<std::string>& sink_,
  ActivityLog& log_,
  std::string label_
)
    : sink(sink_), log(log_), label(label_)
{
    log_.AddChannel(label_, *this);
}

// When the log channel is passed a string both log it and pass it on
void LogChannel::WriteData(std::string const& data)
{
    ActivityLogLine entry;
    entry.label = label;
    entry.content = data;
    log.WriteData(entry);
    sink.WriteData(data);
}

// When an activity log line is replayed back to us, log it as a replay
void LogChannel::WriteData(ActivityLogLine const& data)
{
    log.WriteData({data.label + "Replay", data.content });
    sink.WriteData(data.content);
}

    }
}

