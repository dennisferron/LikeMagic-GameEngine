#pragma once

namespace IoDbg {

template <typename T>
class AbstractInput
{
public:
    virtual ~AbstractInput() {}
    virtual bool HasData() const = 0;
    virtual T ReadData() = 0;
};

}
