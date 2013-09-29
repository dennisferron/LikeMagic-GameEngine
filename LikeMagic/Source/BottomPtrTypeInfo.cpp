// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Utility/BottomPtrTypeInfo.hpp"

namespace LM {

class BottomPtrTypeInfo : public AbstractTypeInfo
{
public:
    virtual std::string get_system() const;
    virtual bool less(const AbstractTypeInfo& other) const;
    virtual bool equals(const AbstractTypeInfo& other) const;
    virtual std::size_t calc_hash() const;
    virtual std::string description() const;
    virtual TypeInfoPtr as_const() const;
    virtual TypeInfoPtr as_nonconst() const;
    virtual TypeInfoPtr as_ptr() const;
    virtual TypeInfoPtr as_value() const;
    virtual TypeInfoPtr class_type() const;
};

LIKEMAGIC_API TypeInfoPtr create_bottom_ptr_type_info()
{
    return new BottomPtrTypeInfo();
}

LIKEMAGIC_API TypeIndex create_bottom_ptr_type_index()
{
    return get_index(new BottomPtrTypeInfo());
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

TypeInfoPtr BottomPtrTypeInfo::as_const() const
{
    return this;
}

TypeInfoPtr BottomPtrTypeInfo::as_nonconst() const
{
    return this;
}

TypeInfoPtr BottomPtrTypeInfo::as_ptr() const
{
    return this;
}

TypeInfoPtr BottomPtrTypeInfo::as_value() const
{
    return this;
}

TypeInfoPtr BottomPtrTypeInfo::class_type() const
{
    return this;
}

}
