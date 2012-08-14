#include <iostream>
#include "boost/shared_ptr.hpp"

namespace Iocaste { namespace Debugger {

class Configuration
{
public:
    virtual ~Configuration();
    virtual std::istream& get_from_log()  = 0;
    virtual std::ostream& get_to_log()  = 0;
    virtual std::istream& get_from_user()  = 0;
    virtual std::ostream& get_to_user()  = 0;
    virtual std::istream& get_from_gdb()  = 0;
    virtual std::ostream& get_to_gdb()  = 0;
};

boost::shared_ptr<Configuration> getConfiguration();

}}
