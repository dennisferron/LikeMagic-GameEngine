#pragma once

#include "AbstractOutput.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T>
class AbstractAdapter : public AbstractOutput<T>
{
public:
    virtual ~AbstractAdapter() {}
};

    }
}
