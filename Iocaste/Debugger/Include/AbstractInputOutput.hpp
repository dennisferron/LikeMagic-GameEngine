#pragma once

#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"

namespace Iocaste {
    namespace Debugger {

template <typename T>
class AbstractInputOutput : public AbstractInput, public AbstractOutput
{
};

    }
}
