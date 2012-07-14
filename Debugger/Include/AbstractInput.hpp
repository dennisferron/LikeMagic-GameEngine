#pragma once

namespace Iocaste {
    namespace Debugger {

struct InputComponentTag {};

template <typename T>
class AbstractInput : public InputComponentTag
{
public:
    virtual bool HasData() const = 0;
    virtual T ReadData() = 0;
};

    }
}
