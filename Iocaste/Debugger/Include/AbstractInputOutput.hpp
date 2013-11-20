#pragma once

#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"

namespace IoDbg {

template <typename T>
class AbstractInputOutput : public AbstractInput, public AbstractOutput
{
};

}
