// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#include "Iocaste/LikeMagicAdapters/IoObjectExpr.hpp"
#include "Iocaste/LikeMagicAdapters/API_Io_Impl.hpp"
#include "Iocaste/LikeMagicAdapters/FromIoTypeInfo.hpp"

using namespace LM;

namespace Iocaste { namespace LMAdapters {

IoObjectExpr::IoObjectExpr(IoObject* io_object_) : Expr(io_object_, FromIoTypeInfo::create_index(get_type_name(io_object)))
{
}

ExprPtr IoObjectExpr::create(IoObject* io_object)
{
    return new IoObjectExpr(io_object);
}

std::string IoObjectExpr::description() const
{
    return std::string("an Io object of type '") + get_type_name(io_object) + "'";
}

void IoObjectExpr::mark() const
{
    IoObject_shouldMarkIfNonNull(io_object);
}

}}
