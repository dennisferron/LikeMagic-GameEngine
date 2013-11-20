#pragma once

#include "AbstractOutput.hpp"

namespace IoDbg {

template <typename T>
class AbstractAdapter : public AbstractOutput<T>
{
public:
    virtual ~AbstractAdapter() {}
};

}
