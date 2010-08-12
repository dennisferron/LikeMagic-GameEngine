// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Backends/Io/IoObjectExpr.hpp"
#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/Backends/Io/FromIoTypeInfo.hpp"

using namespace LikeMagic::Utility;

namespace LikeMagic { namespace Backends { namespace Io {


IoObjectExpr::IoObjectExpr(IoObject* io_object_) : io_object(io_object_), type_info(FromIoTypeInfo::create(get_type_name(io_object)))
{
}

TypeInfoPtr IoObjectExpr::get_type() const
{
    return type_info;
}

std::string IoObjectExpr::description() const
{
    return std::string("an Io object of type '") + get_type_name(io_object) + "'";
}

void IoObjectExpr::mark() const
{
    IoObject_shouldMarkIfNonNull(io_object);
}


}}}
