#include <string>

namespace Iocaste { namespace Debugger {

struct ActivityLogLine
{
    std::string label;
    std::string content;

    bool Parse(std::string str);
    bool Write(std::string& generated) const;
};

}}
