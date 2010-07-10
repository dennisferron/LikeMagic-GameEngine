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

class FromIoTypeInfo : public AbstractTypeInfo
{
private:
    std::string type_name;

protected:

    virtual std::type_info const* comparator_typeid() const
    {
        return &typeid(this);
    }

    virtual bool less(const AbstractTypeInfo& other) const
    {
        FromIoTypeInfo const& that = static_cast<FromIoTypeInfo const&>(other);
        return this->type_name < that.type_name;
    }

public:

    FromIoTypeInfo(std::string type_name_) : type_name(type_name_) {}

    virtual std::string describe() const
    {
        return "From Io Type " + type_name;
    }

    virtual boost::shared_ptr<AbstractTypeInfo const> clone() const
    {
        return boost::shared_ptr<AbstractTypeInfo const>(new FromIoTypeInfo(*this));
    }

};


}}}
