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

void add_class_to_observer(ITypeSystemObserver* observer, AbstractClass const* class_, set<TypeIndex>& already_registered)
{
    if (already_registered.find(class_->get_type()) == already_registered.end())
    {
        already_registered.insert(class_->get_type());

        // Have to register the bases before you register the derived classes.
        auto bases = class_->get_base_classes();
        for (auto base=bases.begin(); base != bases.end(); base++)
            add_class_to_observer(observer, *base, already_registered);

        observer->register_class(class_->get_type(), class_);
    }
}

void AbstractTypeSystem::add_type_system_observer(ITypeSystemObserver* observer)
{
    // If this is the first time adding the observer, catch them up on what has been set up.
    if (observers.find(observer) == observers.end())
    {
        auto types = get_registered_types();
        set<TypeIndex> already_registered;

        // Register all the classes
        for (auto it=types.begin(); it != types.end(); it++)
        {
            auto class_ = get_class(*it);

            if (!(*it == class_->get_type()))
            {
                cout << "Class name is " << class_->get_class_name() << " and ts class name is " << get_class_name(*it) << endl;
                cout << "Error!  ts type " << it->get_id() << " != " << " class type " << class_->get_type().get_id() << endl;
                cout << endl;
            }

            //cout << class_->get_class_name() << " ts iterator num methods is " << get_method_names(*it).size() << endl;
            //cout << "class " << class_->get_class_name() << " num methods is " << class_->get_method_names().size() << endl;
            //cout << class_->get_class_name() << " ts get type num methods is " << get_method_names(class_->get_type()).size() << endl;

            add_class_to_observer(observer, class_, already_registered);

            // Observer will register the methods itself -?
            //auto methods = class_->get_method_names();
            //for (auto method = methods.begin(); method != methods.end(); ++method)
            //    observer->register_method(class_, *method, NULL);
        }
    }

    observers.insert(observer);
}

void AbstractTypeSystem::register_base(LikeMagic::Marshaling::AbstractClass* class_, LikeMagic::Marshaling::AbstractClass const* base)
{
    for (auto it=observers.begin(); it!=observers.end(); ++it)
        (*it)->register_base(class_, base);
}

void AbstractTypeSystem::register_method(LikeMagic::Marshaling::AbstractClass* class_, std::string method_name, LikeMagic::Marshaling::AbstractCallTargetSelector* method)
{
    for (auto it=observers.begin(); it!=observers.end(); ++it)
        (*it)->register_method(class_, method_name, method);
}

void AbstractTypeSystem::add_class(TypeIndex index, AbstractClass* class_ptr)
{
    if (!index.is_class_type())
        throw std::logic_error("add_class index to be a class type!");

    //classes[index] = class_ptr;

    if (classes2.size() <= index.get_class_id())
        classes2.resize(index.get_class_id()+1, NULL);

    classes2[index.get_class_id()] = class_ptr;

    // This needs to be done at the end so that observers that access the class through type system can get to it.
    for (auto it=observers.begin(); it!=observers.end(); ++it)
        (*it)->register_class(index, class_ptr);
}


AbstractTypeSystem::~AbstractTypeSystem()
{
    //std::cout << "Typesystem destructed" << std::endl;

    //for (auto it=classes.begin(); it != classes.end(); it++)
    //{
    //    delete it->second;
    //}

    for (auto it=classes2.begin(); it != classes2.end(); it++)
    {
        delete *it;
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
    //char const* descr = type.describe().c_str();

    //TypeInfoPtr info = type.get_info();
    //TypeInfoPtr bare = info->bare_type();
    //TypeIndex old_index = bare->get_index();
    //TypeIndex index = type.class_type();
    //bool found = (classes.find(index) != classes.end());
    //return found;

    std::size_t pos = type.get_class_id();
    std::size_t sz = classes2.size();
    bool found2 = (
        (pos < sz) && (classes2[pos] != NULL)
    );

    //if (found != found2)
    //    throw std::logic_error("has_class problem");

    return found2;
}

AbstractClass* AbstractTypeSystem::get_class(TypeIndex type) const
{
    if (has_class(type))
    {
        //AbstractClass* p1 = classes.find(type.class_type())->second;
        AbstractClass* p2 = classes2[type.get_class_id()];

        //if (p1 != p2)
        //    throw std::logic_error("get_class problem");

        return p2;
    }
    else
        return unknown_class;
}

TypeInfoList AbstractTypeSystem::get_registered_types() const
{
    TypeInfoList list;

    //for (auto it=classes.begin(); it != classes.end(); it++)
    //    list.push_back(it->first);

    for (std::size_t i=0; i < classes2.size(); i++)
        if (classes2[i])
            list.push_back(TypeIndex(i,i));

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



