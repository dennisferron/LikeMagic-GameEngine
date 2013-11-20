#pragma once

namespace IoDbg {

template <typename T>
class AbstractOutput
{
public:
    ~AbstractOutput() {}
    virtual void WriteData(T const& data) = 0;
};

}
