// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Exprs/AbstractExpression.hpp"

#include <stdexcept>

namespace LM {

void intrusive_ptr_add_ref(AbstractExpression* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(AbstractExpression* p)
{
    if (!--(p->ref_count))
        delete p;
}

AbstractExpression::~AbstractExpression()
{
    //std::cout << "~AbstractExpression " << this << std::endl;
    if (ref_count)
    {
        std::cout << "Fatal error:  Deleting abstract expression when ref_count is nonzero: ref_count = " << ref_count << std::endl;
        std::terminate();
    }
}

AbstractExpression::AbstractExpression() : ref_count(0) {}

void AbstractExpression::set_disable_to_script(bool value) {}
void AbstractExpression::set_auto_delete_ptr(bool value) {}

}
