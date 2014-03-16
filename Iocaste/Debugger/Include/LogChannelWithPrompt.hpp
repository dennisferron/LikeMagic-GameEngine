#include "AbstractAdapter.hpp"

#include "StringWithPrompt.hpp"

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"

namespace IoDbg {

struct ActivityLogLine;
class ActivityLog;

class LogChannelWithPrompt :
    public AbstractAdapter<StringWithPrompt>,
    public AbstractOutput<ActivityLogLine>
{
private:

    AbstractOutput<StringWithPrompt>& sink;
    AbstractOutput<ActivityLogLine>& log;
    std::string label;

    virtual void WriteData(ActivityLogLine const& data);

public:

/*
    //LogChannelWithPrompt(LogChannelWithPrompt const&) = delete;
*/

    LogChannelWithPrompt(
            AbstractOutput<StringWithPrompt>& sink_,
            ActivityLog& log_,
            std::string label_);

    virtual void WriteData(StringWithPrompt const& data);
};

}
