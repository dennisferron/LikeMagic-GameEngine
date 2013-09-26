// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "Iocaste/LikeMagicAdapters/IoVM.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io.hpp"

#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/IMarkable.hpp"
#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

#include <tuple>

namespace Iocaste { namespace LMAdapters {

using LM::TypeSystem;
using namespace LM;
using namespace LM;

class ToIoTypeInfo : public AbstractTypeInfo
{
private:
    std::string type_name;

    ToIoTypeInfo() : type_name("<unspecified>") {}
    ToIoTypeInfo(std::string type_name_) : type_name(type_name_) {}

protected:

    virtual std::string get_system() const
    {
        return "Io (to)";
    }

    virtual bool less(const AbstractTypeInfo& other) const
    {
        ToIoTypeInfo const& that = static_cast<ToIoTypeInfo const&>(other);
        return this->type_name < that.type_name;
    }

    virtual bool equals(const AbstractTypeInfo& other) const
    {
        ToIoTypeInfo const& that = static_cast<ToIoTypeInfo const&>(other);
        return this->type_name == that.type_name;
    }

    virtual std::size_t calc_hash() const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, type_name);
        return seed;
    }

public:

    static TypeInfoPtr create() { return new ToIoTypeInfo(); }
    static TypeInfoPtr create(std::string type_name) { return new ToIoTypeInfo(type_name); }

    static TypeIndex create_index()
    {
        static TypeInfoPtr info = create();
        return type_info_cache_instance->get_index(
                info, info
        );
    }

    static TypeIndex create_index(std::string type_name)
    {
        TypeInfoPtr info = create(type_name);
        return type_info_cache_instance->get_index(
                info, info
        );
    }

    virtual std::string description() const
    {
        return "To Io Type " + type_name;
    }

    virtual TypeInfoPtr as_const() const { return this; }
    virtual TypeInfoPtr as_nonconst() const { return this; }
    virtual TypeInfoPtr as_ptr() const { return this; }
    virtual TypeInfoPtr as_value() const { return this; }
    virtual TypeInfoPtr class_type() const { return this; }
};


}}
