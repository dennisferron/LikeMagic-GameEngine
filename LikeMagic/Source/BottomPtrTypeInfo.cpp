// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/BottomPtrTypeInfo.hpp"
#include "LikeMagic/Utility/TypeInfoBaseImpl.hpp"

namespace LM {

class BottomPtrTypeInfo : public TypeInfoBaseImpl
{
public:
    virtual std::string get_system() const;
    virtual bool less(const AbstractTypeInfo& other) const;
    virtual bool equals(const AbstractTypeInfo& other) const;
    virtual std::size_t calc_hash() const;
    virtual std::string description() const;
};

LIKEMAGIC_API TypeInfoPtr create_bottom_ptr_type_info()
{
    return TypeInfoPtr(new BottomPtrTypeInfo());
}

LIKEMAGIC_API TypeIndex create_bottom_ptr_type_index()
{
    return get_index(TypeInfoPtr(new BottomPtrTypeInfo()));
}

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

std::string BottomPtrTypeInfo::description() const
{
    return "NULL";
}

}
