// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/TypeConv/AbstractTypeConverter.hpp"

namespace LikeMagic { namespace TypeConv {

AbstractTypeConverter::AbstractTypeConverter()
    : ref_count(0)
{

}

AbstractTypeConverter::~AbstractTypeConverter()
{
}

float AbstractTypeConverter::cost() const
{
    return 1.0;
}

void intrusive_ptr_add_ref(AbstractTypeConverter const* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(AbstractTypeConverter const* p)
{
    if (!--(p->ref_count))
        delete p;
}

}}
