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
using namespace std;

namespace Iocaste { namespace LMAdapters {

ExprPtr IoObjectExpr::create(IoObject* io_object)
{
    IoObjectExpr* io_obj_expr = new IoObjectExpr(io_object);
    ExprPtr result = create_expr(io_obj_expr, io_obj_expr->get_type());
/*
    cout
        << " ExprPtr=" << result.get()
        << " io_obj_expr=" << io_obj_expr
        << " io_object=" << io_object
        << endl;
*/
    //result->set_auto_delete_ptr(true);
    return result;
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

IoObject* IoObjectExpr::get_io_object() const
{
    return io_object;
}

}}
