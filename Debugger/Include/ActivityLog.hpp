#include <string>

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"

#include "AbstractOutput.hpp"

namespace Iocaste { namespace Debugger {

struct ActivityLogLine;
class LogChannel;

class ActivityLog :
    public AbstractOutput<std::string>,
    private AbstractOutput<ActivityLogLine>
{
private:
    friend class LogChannel;

    AbstractOutput<std::string>& log_file;
    mutable pthread_mutex_t record_mutex;

    boost::unordered_map<
        std::string,
        AbstractOutput<ActivityLogLine>*
    > channels;

    void WriteData(ActivityLogLine const& data);

public:

    ActivityLog(AbstractOutput<std::string>& log_file_);
    void AddChannel(std::string label, AbstractOutput<ActivityLogLine>& channel);

    // Write actual log file line back onto outputs.
    virtual void WriteData(std::string const& data);
};


}}
