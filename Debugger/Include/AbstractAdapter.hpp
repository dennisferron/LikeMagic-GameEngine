#pragma once

#include "AbstractOutput.hpp"

namespace Iocaste {
    namespace Debugger {

struct AdapterComponentTag {};

template <typename T>
class AbstractAdapter : public AbstractOutput<T>, public AdapterComponentTag
{
};

    }
}
