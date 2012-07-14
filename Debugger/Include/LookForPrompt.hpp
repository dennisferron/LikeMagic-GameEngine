#pragma once

#include "AbstractAdapter.hpp"

#include "Thread.hpp"

#include <string>
#include <iostream>

namespace Iocaste {
    namespace Debugger {

class LookForPrompt :
    public AbstractAdapter<std::string>
{
private:
    std::string buffer;
    AbstractOutput<std::string>& output;
    std::string end_marker;
    mutable pthread_mutex_t end_marker_mutex;

public:
    LookForPrompt(AbstractOutput<std::string>& output_, std::string end_marker_);
    virtual void WriteData(std::string const& data);
    std::string get_end_marker() const;
    void set_end_marker(std::string end_marker_);
};

    }
}
