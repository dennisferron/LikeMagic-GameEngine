#include "AbstractOutput.hpp"

#include <string>

#include "boost/shared_ptr.hpp"
#include "boost/unordered_map.hpp"

namespace Iocaste { namespace Debugger {

struct ActivityLogLine
{
    std::string label;
    std::string content;

    bool Parse(std::string str);
    bool Write(std::string& generated) const;
};

class ActivityLog :
    public AbstractOutput<std::string>,
    private AbstractOutput<ActivityLogLine>
{
private:

    AbstractOutput<std::string>& log_file;
    mutable pthread_mutex_t record_mutex;

    struct Channel;
    friend struct Channel;
    boost::unordered_map<
        std::string,
        boost::shared_ptr<Channel>
    > channels;

    struct Channel : public AbstractOutput<std::string>
    {
        std::string label;
        AbstractOutput<std::string>& wrappee;
        AbstractOutput<ActivityLogLine>& log;

        Channel(std::string label_,
                AbstractOutput<std::string>& wrappee_,
                AbstractOutput<ActivityLogLine>& log_);

        virtual void WriteData(std::string const& data);
    };

    void WriteData(ActivityLogLine const& data);

public:

    ActivityLog(AbstractOutput<std::string>& log_file_);
    AbstractOutput<std::string>& Wrap(std::string label, AbstractOutput<std::string>& wrappee);

    // Write actual log file line back onto outputs.
    virtual void WriteData(std::string const& data);
};


}}
