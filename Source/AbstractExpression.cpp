// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/SFMO/AbstractExpression.hpp"

#include <stdexcept>

namespace LikeMagic { namespace SFMO {

void intrusive_ptr_add_ref(AbstractExpression* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(AbstractExpression* p)
{
    if (!--(p->ref_count))
        delete p;
}

bool AbstractExpression::equals(ExprPtr other)
{
    throw std::logic_error("equals() not defined for this type.");
}

}}
