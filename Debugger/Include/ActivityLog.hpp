#include <string>

namespace Iocaste { namespace Debugger {

struct ActivityLogLine
{
    std::string tag;
    std::string content;

    bool Parse(std::string str);
    bool Write(std::string& generated);
};


}}
