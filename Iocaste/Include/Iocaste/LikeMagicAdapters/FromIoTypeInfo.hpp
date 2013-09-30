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
#include "LikeMagic/Utility/TypeInfoBaseImpl.hpp"

#include <tuple>

namespace Iocaste { namespace LMAdapters {

using namespace LM;

class FromIoTypeInfo : public TypeInfoBaseImpl
{
private:
    std::string type_name;

    FromIoTypeInfo(std::string type_name_) : type_name(type_name_) {}

protected:

    virtual std::string get_system() const
    {
        return "Iocaste";
    }

    virtual bool less(const AbstractTypeInfo& other) const
    {
        FromIoTypeInfo const& that = static_cast<FromIoTypeInfo const&>(other);
        return this->type_name < that.type_name;
    }

    virtual bool equals(const AbstractTypeInfo& other) const
    {
        FromIoTypeInfo const& that = static_cast<FromIoTypeInfo const&>(other);
        return this->type_name == that.type_name;
    }

    virtual std::size_t calc_hash() const
    {
        std::size_t seed = 0;
        boost::hash_combine(seed, type_name);
        return seed;
    }

public:

    static TypeInfoPtr create(std::string type_name) { return TypeInfoPtr(new FromIoTypeInfo(type_name)); }

    static TypeIndex create_index(std::string type_name)
    {
        TypeInfoPtr info = create(type_name);
        return get_index(
                info
        );
    }

    virtual std::string description() const
    {
        return "From Io Type " + type_name;
    }
};

}}
