// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/BottomPtrTypeInfo.hpp"

using namespace LM;

std::string BottomPtrTypeInfo::get_system() const
{
    return "NULL";
}

bool BottomPtrTypeInfo::less(const AbstractTypeInfo& other) const
{
    return false;
}

bool BottomPtrTypeInfo::equals(const AbstractTypeInfo& other) const
{
    return true;
}

std::size_t BottomPtrTypeInfo::calc_hash() const
{
    return 0;
}

TypeInfoPtr BottomPtrTypeInfo::create() { return new BottomPtrTypeInfo(); }

TypeIndex BottomPtrTypeInfo::create_index()
{
    TypeInfoPtr info = create();
    return TypeInfoCache::get_instance()->get_index(
            info, info
    );
}

std::string BottomPtrTypeInfo::description() const
{
    return "NULL";
}
