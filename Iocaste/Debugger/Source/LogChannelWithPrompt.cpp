#include <iostream>
#include <string>
#include <complex>
using namespace std;

#include "ActivityLog.hpp"
#include "LogChannelWithPrompt.hpp"
#include "ActivityLogLine.hpp"
using namespace IoDbg;


namespace IoDbg {

AbstractOutput<StringWithPrompt>& no_call_copy_constructor(LogChannelWithPrompt& value)
{
    return static_cast<AbstractOutput<StringWithPrompt>&>(value);
}


LogChannelWithPrompt::LogChannelWithPrompt(
  AbstractOutput<StringWithPrompt>& sink_,
  ActivityLog& log_,
  std::string label_
)
    : sink(sink_), log(log_), label(label_)
{
    log_.AddChannel(label_, *this);
}

// When the log channel is passed a string both log it and pass it on
void LogChannelWithPrompt::WriteData(StringWithPrompt const& data)
{
    ActivityLogLine entry;
    entry.label = label;
    entry.content = data.content + "\b" + data.prompt;
    log.WriteData(entry);
    sink.WriteData(data);
}

// When an activity log line is replayed back to us, log it as a replay
void LogChannelWithPrompt::WriteData(ActivityLogLine const& data)
{
    log.WriteData({data.label + "Replay", data.content });
    size_t divider = data.content.find('\b');
    string msg = data.content.substr(0, divider);
    string prompt = data.content.substr(divider+1);
    sink.WriteData({msg, prompt});
}

}

