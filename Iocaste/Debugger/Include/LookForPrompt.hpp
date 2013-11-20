#pragma once

#include "AbstractInput.hpp"
#include "AbstractAdapter.hpp"
#include "StringWithPrompt.hpp"
#include "boost/optional.hpp"

#include <iostream>

namespace IoDbg {

class LookForPrompt :
    public AbstractAdapter<std::string>
{
private:
    std::string buffer;
    std::string end_marker_str;
    AbstractOutput<StringWithPrompt>& output;
    AbstractInput<std::string>& end_marker_queue;

    // Due to a race condition between "set prompt" and
    // the dialog coming from GDB, when the prompt changes we need to keep the old
    // end marker around until we get the first string with the new marker.
    boost::optional<
        std::string
    > old_end_marker;

public:
    LookForPrompt(AbstractOutput<StringWithPrompt>& output_, AbstractInput<std::string>& end_marker_queue_);
    virtual void WriteData(std::string const& data);
};

}
