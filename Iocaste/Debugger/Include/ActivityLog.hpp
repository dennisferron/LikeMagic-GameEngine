#include <string>

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"

#include "AbstractOutput.hpp"
#include "Queue.hpp"

namespace Iocaste { namespace Debugger {

struct ActivityLogLine;
class TestPlan;

class ActivityLog :
    public AbstractOutput<std::string>,
    public AbstractOutput<ActivityLogLine>
{
private:

    AbstractOutput<std::string>& log_file;
    TestPlan& test_plan;
    mutable boost::mutex record_mutex;

    boost::unordered_map<
        std::string,
        AbstractOutput<ActivityLogLine>*
    > channels;

    boost::unordered_map<
        std::string,
        Queue<ActivityLogLine>
    > pending;

    Queue<ActivityLogLine> test_results;

    void expect(ActivityLogLine test_log_entry, bool exact_match);
    void WriteData(ActivityLogLine const& data);

public:

    ActivityLog(ActivityLog const&) = delete;
    ActivityLog(AbstractOutput<std::string>& log_file_, TestPlan& plan_);
    virtual ~ActivityLog();
    void AddChannel(std::string label, AbstractOutput<ActivityLogLine>& channel);

    // Write actual log file line back onto outputs.
    virtual void WriteData(std::string const& data);
};


}}
