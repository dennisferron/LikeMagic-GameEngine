#pragma once

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Interprocess/AbstractSharedArgMarshaller.hpp"
#include "LikeMagic/binding_functions.hpp"

namespace LM {

template <typename T>
struct MarshalByCopyConstructor : public AbstractSharedArgMarshaller
{
    MarshalByCopyConstructor() {}

    virtual void write(void* location, ExprPtr arg)
    {
        ExprPtr ward;
        *(T*)location = EvalAs<T>::value(arg, ward);
    }

    virtual ExprPtr read(void* location)
    {
        // TODO:  If we can know that the value from the buffer
        // will not be needed longer than the call, we could avoid
        // allocating a new term every time.
        // Actually if it is known all of a method's args are copy
        // by value, could we simply memcpy it onto the stack?
        return LM::Term<T>::create(*((T*)location));
    }

    virtual size_t size() const
    {
        return sizeof(T);
    }
};

}
