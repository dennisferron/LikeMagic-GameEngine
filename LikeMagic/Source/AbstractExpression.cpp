// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Exprs/AbstractExpression.hpp"

#include <stdexcept>

namespace LikeMagic { namespace Exprs {

void intrusive_ptr_add_ref(AbstractExpression* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(AbstractExpression* p)
{
    if (!--(p->ref_count))
        delete p;
}

}}
