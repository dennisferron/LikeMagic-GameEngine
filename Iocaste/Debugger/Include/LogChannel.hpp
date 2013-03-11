#include "AbstractAdapter.hpp"

#include <string>

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"

namespace Iocaste { namespace Debugger {

class ActivityLog;
struct ActivityLogLine;

class LogChannel :
    public AbstractAdapter<std::string>,
    public AbstractOutput<ActivityLogLine>
{
private:

    AbstractOutput<std::string>& sink;
    AbstractOutput<ActivityLogLine>& log;
    std::string label;

    virtual void WriteData(ActivityLogLine const& data);

public:

    LogChannel(LogChannel const&) = delete;

    LogChannel(
            AbstractOutput<std::string>& sink_,
            ActivityLog& log_,
            std::string label_);

    virtual void WriteData(std::string const& data);
};

}}
