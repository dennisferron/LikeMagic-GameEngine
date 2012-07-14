#pragma once

namespace Iocaste {
    namespace Debugger {

struct OutputComponentTag {};

template <typename T>
class AbstractOutput : public OutputComponentTag
{
public:
    virtual void WriteData(T const& data) = 0;
};

    }
}
