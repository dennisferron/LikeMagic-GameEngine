#pragma once

#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Interprocess/AbstractSharedArgMarshaller.hpp"

namespace LikeMagic { namespace Interprocess {

template <typename T>
struct MarshalByCopyConstructor : public AbstractSharedArgMarshaller
{
    MarshalByCopyConstructor() {}

    virtual void write(void* location, ExprPtr arg)
    {
        *(T*)location = type_system->try_conv<T>(arg)->eval();
    }

    virtual ExprPtr read(void* location)
    {
        // TODO:  If we can know that the value from the buffer
        // will not be needed longer than the call, we could avoid
        // allocating a new term every time.
        // Actually if it is known all of a method's args are copy
        // by value, could we simply memcpy it onto the stack?
        return LikeMagic::Exprs::Term<T, true>::create(*((T*)location));
    }

    virtual size_t size() const
    {
        return sizeof(T);
    }
};

}}
