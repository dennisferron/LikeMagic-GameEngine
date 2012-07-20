#include <string>

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"

#include "AbstractOutput.hpp"
#include "Queue.hpp"

namespace Iocaste { namespace Debugger {

struct ActivityLogLine;
class LogChannel;
class TestPlan;

class ActivityLog :
    public AbstractOutput<std::string>,
    private AbstractOutput<ActivityLogLine>
{
private:
    friend class LogChannel;

    AbstractOutput<std::string>& log_file;
    TestPlan& test_plan;
    mutable pthread_mutex_t record_mutex;

    boost::unordered_map<
        std::string,
        AbstractOutput<ActivityLogLine>*
    > channels;

    boost::unordered_map<
        std::string,
        Queue<std::string>
    > pending;

    Queue<ActivityLogLine> test_results;

    void WriteData(ActivityLogLine const& data);

public:

    ActivityLog(ActivityLog const&) = delete;
    ActivityLog(AbstractOutput<std::string>& log_file_, TestPlan& plan_);
    void AddChannel(std::string label, AbstractOutput<ActivityLogLine>& channel);

    // Write actual log file line back onto outputs.
    virtual void WriteData(std::string const& data);
};


}}
