
#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/Marshaling/AbstractClass.hpp"

#include "LikeMagic/TypeConv/NoChangeConv.hpp"

#include <iostream>
using namespace std;

using namespace LikeMagic;

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

AbstractCppObjProxy* AbstractTypeSystem::create_class_proxy(BetterTypeInfo type) const
{
    return get_class(type)->create_class_proxy();
}

bool AbstractTypeSystem::is_ref_to_value_conv(BetterTypeInfo from_type, BetterTypeInfo to_type) const
{
    return from_type.bare_type() == to_type.bare_type() && from_type.is_ptr == to_type.is_ptr && from_type.is_ref && !to_type.is_ref;
}

bool AbstractTypeSystem::is_value_to_ref_conv(BetterTypeInfo from_type, BetterTypeInfo to_type) const
{
    return from_type.bare_type() == to_type.bare_type() && from_type.is_ptr == to_type.is_ptr && !from_type.is_ref && to_type.is_ref && to_type.is_const;
}

bool AbstractTypeSystem::is_nullptr_conv(ExprPtr from, BetterTypeInfo to_type) const
{
    return to_type.is_ptr && dynamic_cast<NullExpr<void*>*>(from.get());
}

bool AbstractTypeSystem::is_const_adding_conv(BetterTypeInfo from_type, BetterTypeInfo to_type) const
{
    return
            from_type.as_const_type() == to_type
        ||
            (
                from_type.is_ptr
            &&
                (
                    from_type.as_ptr_to_const_type() == to_type
                ||
                    from_type.as_const_type().as_ptr_to_const_type() == to_type
                )
            )
        ;
}


ExprPtr AbstractTypeSystem::search_for_conv(ExprPtr from, BetterTypeInfo from_type, BetterTypeInfo to_type) const
{
    return conv_graph.wrap_expr(from, from_type, to_type);

    // Single conversions
    if (has_converter(from_type, to_type))
        return get_converter(from_type, to_type)->wrap_expr(from);

    if (has_converter(from_type.as_const_type(), to_type))
        return get_converter(from_type.as_const_type(), to_type)->wrap_expr(from);

    if (has_converter(from_type, to_type.as_const_type()))
        return get_converter(from_type, to_type.as_const_type())->wrap_expr(from);

    if (has_converter(from_type, to_type.as_nonconst_type()))
        return get_converter(from_type, to_type.as_nonconst_type())->wrap_expr(from);

    if (has_converter(from_type.as_const_type(), to_type.as_nonconst_type()))
        return get_converter(from_type.as_const_type(), to_type.as_nonconst_type())->wrap_expr(from);

    // Double conversions
    //if (from_type.is_ptr && has_converter(from_type, from_type.remove_reference()) && has_converter(from_type.remove_reference(), to_type))
    //    return make_conv_chain(from, std::make_tuple(from_type, from_type.remove_reference(), to_type));

    throw std::logic_error("No type converter from " + from_type.describe() + " to " + to_type.describe());
}

AbstractCppObjProxy* AbstractTypeSystem::call
(
    BetterTypeInfo type,
    std::string method_name,
    AbstractCppObjProxy* proxy,
    std::vector<ExprPtr> args
) const
{
    return get_class(type)->call(proxy, method_name, args);
}

std::vector<std::string> const& AbstractTypeSystem::get_method_names(BetterTypeInfo type) const
{
    return get_class(type)->get_method_names();
}

std::vector<BetterTypeInfo> AbstractTypeSystem::get_arg_types(
    BetterTypeInfo type,
    std::string method_name,
    int num_args
) const
{
    return get_class(type)->get_arg_types(method_name, num_args);
}

bool AbstractTypeSystem::has_class(BetterTypeInfo type) const
{
    return classes.find(type.bare_type()) != classes.end();
}

AbstractClass const* AbstractTypeSystem::get_class(BetterTypeInfo type) const
{
    if (has_class(type))
        return classes.find(type.bare_type())->second;
    else
        return unknown_class;
}

std::vector<BetterTypeInfo>
    AbstractTypeSystem::get_registered_types() const
{
    std::vector<BetterTypeInfo> list;

    for (auto it=classes.begin(); it != classes.end(); it++)
        list.push_back(it->first);

    return list;
}

std::vector<std::string>
    AbstractTypeSystem::get_base_names(BetterTypeInfo type) const
{
    return get_class(type)->get_base_names();
}

std::string AbstractTypeSystem::get_class_name(BetterTypeInfo type) const
{
    std::string name = "";

    if (has_class(type))
        name = get_class(type)->get_class_name();
    else
    {
        name = std::string("Unknown_CppObj");
        std::cout << "warning: nothing registered for type "
            << type.describe() << std::endl;
    }

    return name;
}

bool AbstractTypeSystem::has_converter(BetterTypeInfo from, BetterTypeInfo to) const
{
    auto from_it = converters.find(from);

    return from_it != converters.end()
        && from_it->second.find(to) != from_it->second.end();
}

AbstractTypeConverter const* AbstractTypeSystem::get_converter(BetterTypeInfo from, BetterTypeInfo to) const
{
    if (!has_converter(from, to))
        throw std::logic_error(std::string("No type converter registered from ") + from.describe() + " to " + to.describe());

    auto from_it = converters.find(from);
    auto to_it = from_it->second.find(to);

    return to_it->second;
}


void AbstractTypeSystem::add_converter(BetterTypeInfo from, BetterTypeInfo to, AbstractTypeConverter const* conv)
{
    conv_graph.add_conv(from, to, conv);

    // Support the const forms of this conversion too
    conv_graph.add_conv(from, to.as_const_type(), conv);
    conv_graph.add_conv(from.as_const_type(), to.as_const_type(), conv);

    // Also add converters to make either type const.
    conv_graph.add_conv(from, from.as_const_type(), new NoChangeConv);
    conv_graph.add_conv(to, to.as_const_type(), new NoChangeConv);

    //if (has_converter(from, to))
    //    delete converters[from][to];

    converters[from][to] = conv;
}



