#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_object.hpp>
#include <boost/fusion/include/adapt_struct.hpp>

#include "SharedTypes.hpp"

// Ok because this header should only ever be included in implementation files:
using namespace Iocaste::Debugger;

// Not binding GdbValue because it is a typedef for a variant.
