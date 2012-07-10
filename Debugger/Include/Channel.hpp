
#include "AbstractInput.hpp"
#include "AbstractOutput.hpp"

template <typename ToType, typename FromType>
struct Channel
{
    AbstractOutput<ToType>& to;
    AbstractInput<FromType>& from;

    Channel(AbstractOutput<ToType>& to_, AbstractInput<FromType>& from_)
        : to(to_), from(from_) {}
};
