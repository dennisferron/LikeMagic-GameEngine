// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Backends/Io/IoVM.hpp"
#include "LikeMagic/Backends/Io/API_Io.hpp"

#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/IMarkable.hpp"

#include "LikeMagic/Utility/AbstractTypeInfo.hpp"

#include <tuple>

namespace LikeMagic { namespace Backends { namespace Io {

using LikeMagic::AbstractTypeSystem;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::Utility;

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

    virtual std::string describe() const
    {
        return "To Io Type " + type_name;
    }
};


}}}
