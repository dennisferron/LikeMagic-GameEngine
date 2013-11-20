#pragma once

#include "AbstractInput.hpp"

#include <string>
#include <iostream>

namespace IoDbg {

class CharInput :
    public AbstractInput<std::string>
{
private:
    std::istream& stream;

public:
    CharInput(std::istream& stream_);
    virtual bool HasData() const;
    virtual std::string ReadData();
};

}
