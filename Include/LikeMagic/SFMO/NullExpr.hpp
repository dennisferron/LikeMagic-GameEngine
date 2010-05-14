
#pragma once

#include "Expression.hpp"

#include "../Utility/TypeDescr.hpp"
#include <iostream>
#include <stdexcept>

namespace LikeMagic { namespace SFMO {

// When IoNil is encountered, it is marshaled as a NullExpr<void*> object,
// which is an expression of type of void* that always returns NULL.
// Some fancy magic happens in try_conv to intercept the void* NULL value
// and replace it with one of the appropriate pointer type for a function argument.
template <typename T>
class NullExpr : public Expression<T>
{
    static_assert(boost::is_pointer<T>::value, "Cannot create NullExpr for type that is not a pointer!");
private:
    NullExpr() {}

public:
    static boost::intrusive_ptr<Expression<T>> create() { return new NullExpr(); }

    inline virtual T eval() { return NULL; }
    virtual boost::intrusive_ptr<Expression<T>> clone() const { return new NullExpr(); }
    virtual bool is_terminal() const { return true; }
    virtual bool is_lazy() const { return false; }

    virtual std::string description() const
    {
        return std::string("NULL");
    }

    virtual void mark() const {}
};

}}
