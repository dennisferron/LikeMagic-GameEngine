#include <string>

namespace Iocaste { namespace Debugger {

struct ActivityLogLine
{
    std::string label;
    std::string content;

    void Parse(std::string str);
    void Write(std::string& generated) const;
};

}}
