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

ExprPtr IoObjectExpr::create(IoObject* io_object)
{
    auto* result = new IoObjectExpr(io_object);
    return create_expr(result, result->get_type());
}

IoObjectExpr::IoObjectExpr(IoObject* io_object_) :
    io_object(io_object_), io_type(FromIoTypeInfo::create_index(get_type_name(io_object)))
{
}

TypeIndex IoObjectExpr::get_type() const
{
    return io_type;
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
