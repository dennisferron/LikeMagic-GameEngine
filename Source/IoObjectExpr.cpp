// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "LikeMagic/Backends/Io/IoObjectExpr.hpp"
#include "LikeMagic/Backends/Io/API_Io_Impl.hpp"
#include "LikeMagic/Utility/BetterTypeInfo.hpp"

using namespace LikeMagic::Utility;

namespace LikeMagic { namespace Backends { namespace Io {


IoObjectExpr::IoObjectExpr(IoObject* io_object_) : io_object(io_object_) {}

BetterTypeInfo IoObjectExpr::get_type() const
{
    return BetterTypeInfo::create<IoObjectExprTag>();
}

std::string IoObjectExpr::description() const
{
    return std::string("an Io object of type '") + IoObject_tag(io_object)->name + "'";
}

void IoObjectExpr::mark()
{
    IoObject_shouldMarkIfNonNull(io_object);
}


}}}
