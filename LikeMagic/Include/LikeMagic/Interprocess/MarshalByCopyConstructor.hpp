#pragma once

namespace LikeMagic { namespace Interprocess {

template <typename T>
struct MarshalByCopyConstructor
{
    LikeMagic::AbstractTypeSystem const& type_system;

    MarshalByCopy(LikeMagic::AbstractTypeSystem const& type_system_)
        : type_system(type_system)

    virtual void write(void* location, ExprPtr arg)
    {
        *(T*)location = type_system.try_conv<T>(arg);
    }

    virtual ExprPtr read(void* location)
    {
        // TODO:  If we can know that the value from the buffer
        // will not be needed longer than the call, we could avoid
        // allocating a new term every time.
        // Actually if it is known all of a method's args are copy
        // by value, could we simply memcpy it onto the stack?
        return Term<T, true>::create(*((T*)location));
    }

    virtual size_t size() const
    {
        return sizeof(T);
    }
};

}}
