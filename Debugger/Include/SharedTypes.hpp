#pragma once

#include <string>
#include <vector>
#include "boost/optional.hpp"
#include "boost/variant.hpp"

namespace Iocaste { namespace Debugger { namespace SharedTypes {

typedef boost::variant<
    int, std::string
> GdbValue;

}}}
