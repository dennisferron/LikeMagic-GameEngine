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

#include <set>

#include <iostream>
using namespace std;

using namespace LikeMagic;

AbstractTypeSystem::~AbstractTypeSystem()
{
    //std::cout << "Typesystem destructed" << std::endl;

    for (auto it=classes.begin(); it != classes.end(); it++)
    {
        delete it->second;
    }
}


ExprPtr AbstractTypeSystem::try_conv(ExprPtr from_expr, TypeIndex to_type) const
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

bool AbstractTypeSystem::has_conv(TypeIndex from_type, TypeIndex to_type) const
{
    return conv_graph.has_conv(from_type, to_type);
}


AbstractTypeSystem::AbstractTypeSystem() : leak_memory_flag(false)
{
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

AbstractCppObjProxy* AbstractTypeSystem::create_class_proxy(TypeIndex type) const
{
    return get_class(type)->create_class_proxy();
}


AbstractCppObjProxy* AbstractTypeSystem::call
(
    TypeIndex type,
    std::string method_name,
    AbstractCppObjProxy* proxy,
    std::vector<ExprPtr> args
) const
{
    return get_class(type)->call(proxy, method_name, args);
}

std::vector<std::string> const& AbstractTypeSystem::get_method_names(TypeIndex type) const
{
    return get_class(type)->get_method_names();
}

TypeInfoList AbstractTypeSystem::get_arg_types(
    TypeIndex type,
    std::string method_name,
    int num_args
) const
{
    return get_class(type)->get_arg_types(method_name, num_args);
}

bool AbstractTypeSystem::has_class(TypeIndex type) const
{
    return classes.find(type.get_info()->bare_type()->get_index()) != classes.end();
}

AbstractClass const* AbstractTypeSystem::get_class(TypeIndex type) const
{
    if (has_class(type))
        return classes.find(type.get_info()->bare_type()->get_index())->second;
    else
        return unknown_class;
}

TypeInfoList AbstractTypeSystem::get_registered_types() const
{
    TypeInfoList list;

    for (auto it=classes.begin(); it != classes.end(); it++)
        list.push_back(it->first);

    return list;
}

std::vector<std::string>
    AbstractTypeSystem::get_base_names(TypeIndex type) const
{
    return get_class(type)->get_base_names();
}

std::string AbstractTypeSystem::get_class_name(TypeIndex type) const
{
    std::string name = "";

    if (has_class(type))
        name = get_class(type)->get_class_name();
    else
    {
        name = std::string("Unknown_CppObj");
        std::cout << "warning: nothing registered for type "
            << type.describe() << std::endl;
        //throw std::logic_error("Nothing registered for type " + type.describe());
    }

    return name;
}


void AbstractTypeSystem::add_type(TypeIndex type)
{
    conv_graph.add_type(type);
}

void AbstractTypeSystem::add_converter_simple(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    conv_graph.add_conv(from, to, conv);
}

void AbstractTypeSystem::add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    conv_graph.add_conv(from, to, conv);

    // Support the const forms of this conversion too
    conv_graph.add_conv(from, to.get_info()->as_const_type()->get_index(), conv);
    conv_graph.add_conv(from.get_info()->as_const_type()->get_index(), to.get_info()->as_const_type()->get_index(), conv);

    // Also add converters to make either type const.
    conv_graph.add_conv(from, from.get_info()->as_const_type()->get_index(), new NoChangeConv);
    conv_graph.add_conv(to, to.get_info()->as_const_type()->get_index(), new NoChangeConv);

    // Allow this expression type to be converted to an expression.
    TypeIndex to_expr_type = BetterTypeInfo::create_index<ExprPtr>();
    conv_graph.add_conv(from, to_expr_type, new ToAbstractExpressionConv);
    conv_graph.add_conv(from.get_info()->as_const_type()->get_index(), to_expr_type, new ToAbstractExpressionConv);

    // Allow NULL (aka nil) to be converted to pointers to these types.
    auto nil_tag = BetterTypeInfo::create_index<NilExprTag*>();

    if (from.get_info()->get_is_ptr())
        conv_graph.add_conv(nil_tag, from, new NilConv);

    if (to.get_info()->get_is_ptr())
        conv_graph.add_conv(nil_tag, to, new NilConv);

}



