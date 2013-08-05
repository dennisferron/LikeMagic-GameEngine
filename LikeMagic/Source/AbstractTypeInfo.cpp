// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

namespace LikeMagic { namespace Utility {

void intrusive_ptr_add_ref(AbstractTypeInfo const* p)
{
    ++(p->ref_count);
}

void intrusive_ptr_release(AbstractTypeInfo const* p)
{
    if (!--(p->ref_count))
        delete p;
}

AbstractTypeInfo::AbstractTypeInfo() :
    ref_count(0), has_cached_hash(false)
{
}

AbstractTypeInfo::~AbstractTypeInfo()
{
}

TypeIndex AbstractTypeInfo::get_index() const
{
    return TypeInfoCache::get_instance()->get_index(this, this->bare_type());
}

}}
