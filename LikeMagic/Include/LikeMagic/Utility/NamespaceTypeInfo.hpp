// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once


#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

namespace LM {

class NamespaceTypeInfo : public AbstractTypeInfo
{
private:
    std::string namespace_name;
    NamespaceTypeInfo(std::string namespace_name_);
protected:
    virtual std::string get_system() const;
    virtual bool less(const AbstractTypeInfo& other) const;
    virtual bool equals(const AbstractTypeInfo& other) const;
    virtual std::size_t calc_hash() const;
public:
    static TypeInfoPtr create(std::string namespace_name);
    static TypeIndex create_index(std::string namespace_name);
    virtual std::string description() const;
    virtual TypeInfoPtr as_const() const;
    virtual TypeInfoPtr as_nonconst() const;
    virtual TypeInfoPtr as_ptr() const;
    virtual TypeInfoPtr as_value() const;
    virtual TypeInfoPtr class_type() const;
};


}
