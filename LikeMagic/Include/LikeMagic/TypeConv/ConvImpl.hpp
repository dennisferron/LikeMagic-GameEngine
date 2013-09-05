
#include "LikeMagic/Exprs/ValuePtr.hpp"

namespace LM {

struct ConvImpl
{
    virtual ValuePtr do_conv(ValuePtr value) const = 0;
};

}
