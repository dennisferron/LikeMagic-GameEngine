// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/Marshaling/AbstractClass.hpp"

#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/SFMO/NullExpr.hpp"
#include "LikeMagic/TypeConv/NilConv.hpp"
#include "LikeMagic/TypeConv/ToAbstractExpressionConv.hpp"

#include <iostream>
using namespace std;

using namespace LikeMagic;

ExprPtr AbstractTypeSystem::try_conv(ExprPtr from_expr, TypeInfoPtr to_type) const
{
    try
    {
        return conv_graph.wrap_expr(from_expr, from_expr->get_type(), to_type);
    }
    catch (std::logic_error const& le)
    {
        throw std::logic_error(le.what() + std::string(" Note: From expression is ") + from_expr->description());
    }
}

bool AbstractTypeSystem::has_conv(TypeInfoPtr from_type, TypeInfoPtr to_type) const
{
    return conv_graph.has_conv(from_type, to_type);
}


AbstractTypeSystem::AbstractTypeSystem() : leak_memory_flag(false)
{
    // Allow conversions from nil to any pointer.
    conv_graph.add_type(BetterTypeInfo::create<IoNilExprTag*>());
}

void AbstractTypeSystem::print_type_graph() const
{
    conv_graph.print_graph();
}

bool AbstractTypeSystem::leak_memory() const
{
    return leak_memory_flag;
}

void AbstractTypeSystem::set_leak_memory(bool flag)
{
    leak_memory_flag = flag;
}

AbstractCppObjProxy* AbstractTypeSystem::create_class_proxy(TypeInfoPtr type) const
{
    return get_class(type)->create_class_proxy();
}


AbstractCppObjProxy* AbstractTypeSystem::call
(
    TypeInfoPtr type,
    std::string method_name,
    AbstractCppObjProxy* proxy,
    std::vector<ExprPtr> args
) const
{
    return get_class(type)->call(proxy, method_name, args);
}

std::vector<std::string> const& AbstractTypeSystem::get_method_names(TypeInfoPtr type) const
{
    return get_class(type)->get_method_names();
}

TypeInfoList AbstractTypeSystem::get_arg_types(
    TypeInfoPtr type,
    std::string method_name,
    int num_args
) const
{
    return get_class(type)->get_arg_types(method_name, num_args);
}

bool AbstractTypeSystem::has_class(TypeInfoPtr type) const
{
    return classes.find(type->bare_type()) != classes.end();
}

AbstractClass const* AbstractTypeSystem::get_class(TypeInfoPtr type) const
{
    if (has_class(type))
        return classes.find(type->bare_type())->second;
    else
        return unknown_class;
}

TypeInfoList
    AbstractTypeSystem::get_registered_types() const
{
    TypeInfoList list;

    for (auto it=classes.begin(); it != classes.end(); it++)
        list.push_back(it->first.key);

    return list;
}

std::vector<std::string>
    AbstractTypeSystem::get_base_names(TypeInfoPtr type) const
{
    return get_class(type)->get_base_names();
}

std::string AbstractTypeSystem::get_class_name(TypeInfoPtr type) const
{
    std::string name = "";

    if (has_class(type))
        name = get_class(type)->get_class_name();
    else
    {
        name = std::string("Unknown_CppObj");
        std::cout << "warning: nothing registered for type "
            << type->describe() << std::endl;
        //throw std::logic_error("Nothing registered for type " + type.describe());
    }

    return name;
}


void AbstractTypeSystem::add_type(TypeInfoPtr type)
{
    conv_graph.add_type(type);
}

void AbstractTypeSystem::add_converter_simple(TypeInfoPtr from, TypeInfoPtr to, AbstractTypeConverter const* conv)
{
    conv_graph.add_conv(from, to, conv);
}

void AbstractTypeSystem::add_converter_variations(TypeInfoPtr from, TypeInfoPtr to, AbstractTypeConverter const* conv)
{
    conv_graph.add_conv(from, to, conv);

    // Support the const forms of this conversion too
    conv_graph.add_conv(from, to->as_const_type(), conv);
    conv_graph.add_conv(from->as_const_type(), to->as_const_type(), conv);

    // Also add converters to make either type const.
    conv_graph.add_conv(from, from->as_const_type(), new NoChangeConv);
    conv_graph.add_conv(to, to->as_const_type(), new NoChangeConv);

    // Allow NULL (aka nil) to be converted to these types.
    auto nil_tag = BetterTypeInfo::create<IoNilExprTag*>();

    // Allow this expression type to be converted to an expression.
    TypeInfoPtr to_expr_type = BetterTypeInfo::create<ExprPtr>();
    conv_graph.add_conv(from, to_expr_type, new ToAbstractExpressionConv);
    conv_graph.add_conv(from->as_const_type(), to_expr_type, new ToAbstractExpressionConv);

    if (from->get_is_ptr())
        conv_graph.add_conv(nil_tag, from, new NilConv);

    if (to->get_is_ptr())
        conv_graph.add_conv(nil_tag, to, new NilConv);

}



