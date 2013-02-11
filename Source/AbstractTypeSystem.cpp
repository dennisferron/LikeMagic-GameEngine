// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/AbstractTypeSystem.hpp"
#include "LikeMagic/Marshaling/AbstractClass.hpp"

#include "LikeMagic/TypeConv/NoChangeConv.hpp"
#include "LikeMagic/TypeConv/ImplicitConv.hpp"
#include "LikeMagic/TypeConv/GenericConv.hpp"
#include "LikeMagic/TypeConv/ToAbstractExpressionConv.hpp"
#include "LikeMagic/TypeConv/PtrDerefConv.hpp"
#include "LikeMagic/TypeConv/AddrOfConv.hpp"

using namespace LikeMagic::TypeConv;

#include <set>

#include <iostream>
using namespace std;

using namespace LikeMagic;

// Stuck here because compiler complains when it is pure virtual:
ITypeSystemObserver::~ITypeSystemObserver() {}


template <typename From, typename To>
void AbstractTypeSystem::add_nochange_conv(TypeInfoPtr from, TypeInfoPtr to)
{
    if (!(from->get_index() == to->get_index()))
        conv_graph.add_conv(from->get_index(), to->get_index(), new NoChangeConv<From, To>());
}

template <typename From, typename To>
void AbstractTypeSystem::add_generic_conv(TypeInfoPtr from, TypeInfoPtr to)
{
    conv_graph.add_conv(from->get_index(), to->get_index(), new GenericConv<From, To>(from, to));
}


/*

The rules for const pointer conversions in C++ get complex quickly.
Just considering const objects, const pointers, and references to pointers,
there are 8 kinds of pointers and 256 combinations, some legal some not.

Since I'm reading Pierce's Basic Category Theory for Computer Scientists
at the moment I got the idea to make a diagram of objects and arrows.
I realized you could divide the diagram into two horizontal tracks:
one for const objects and one for nonconst.  They have the same structure.

Furthermore you can go from the nonconst track to the const track, but you cannot
go from the bottom (const) track back up to the top (nonconst) track.

You can also divide the diagram on a vertical line where reference types
are freely convertible with a value type; T*const& <=> T*const and
T const*const& <=> T const*const.  The halves are not entirely symmetrical
because nonconst references cannot reference const references or values,
whereas nonconst and const values can be freely assigned to eash other because
the bits are copied when they are assigned.

          Nonconst           Const          |          Const         Nonconst
          Reference        Reference        |          Value          Value
--------------------------------------------------------------------------------
                                            |
Nonconst    +---+          +--------+ ======|=====> +-------+ ------> +--+
Object      |T*&| -------> |T*const&|       |       |T*const|         |T*|
Track       +---+          +--------+ <=====|====== +-------+ <------ +--+
              |                 |           |           |               |
--------------|-----------------|-----------------------|---------------|-------
              |                 |           |           |               |
              v                 v           |           v               v
Const    +---------+     +--------------+ ==|=> +-------------+ --> +--------+
Object   |T const*&| --> |T const*const&|   |   |T const*const|     |T const*|
Track    +---------+     +--------------+ <=|== +-------------+ <-- +--------+
                                            |
--------------------------------------------------------------------------------
Key:  --> NoChangeConv                      |
      ==> GenericConv                       |
*/

// handles const object or nonconst object.  T is either const void or just void.
template <typename T>
void AbstractTypeSystem::add_conv_track(TypeInfoPtr type)
{
    auto as_ptr_ref = type->as_ptr()->as_ref();
    auto as_ptr_const_ref = type->as_ptr()->as_const_ptr_type()->as_ref();
    auto as_ptr_const_val = type->as_ptr()->as_const_ptr_type();
    auto as_ptr_val = type->as_ptr();

    // Making a reference const does not change the implementation.
    add_nochange_conv<T*&, T*const&>(as_ptr_ref, as_ptr_const_ref);

    // Reciprocally convert const ref and const value with a generic conv.
    add_generic_conv<T*const&, T*const>(as_ptr_const_ref, as_ptr_const_val);
    add_generic_conv<T*const, T*const&>(as_ptr_const_val, as_ptr_const_ref);

    // Reciprocally convert const and nonconst ptr values with no change in the impl.
    add_nochange_conv<T*const, T*>(as_ptr_const_val, as_ptr_val);
    add_nochange_conv<T*, T*const>(as_ptr_val, as_ptr_const_val);

    // For the nonconst track, add all the conversions to the const track.
    // (These will be nop's if we are already on the const track)
    add_nochange_conv<T*&, T const*&>(as_ptr_ref, as_ptr_ref->as_const_obj_type());
    add_nochange_conv<T*const&, T const*const&>(as_ptr_const_ref, as_ptr_const_ref->as_const_obj_type());
    add_nochange_conv<T*const , T const*const >(as_ptr_const_val, as_ptr_const_val->as_const_obj_type());
    add_nochange_conv<T* , T const* >(as_ptr_val, as_ptr_val->as_const_obj_type());
}

// Missing AbstractTypeSystem:: here is not a mistake - it's a helper function for this cpp file, not a member function.
void add_class_to_observer(ITypeSystemObserver* observer, AbstractClass const* class_, set<TypeIndex>& already_registered)
{
    if (already_registered.find(class_->get_type()) == already_registered.end())
    {
        already_registered.insert(class_->get_type());

        // Have to register the bases before you register the derived classes.
        auto bases = class_->get_base_classes();
        for (auto base=bases.begin(); base != bases.end(); base++)
            add_class_to_observer(observer, *base, already_registered);

        observer->register_class(class_);
    }
}

void AbstractTypeSystem::add_type_system_observer(ITypeSystemObserver* observer)
{
    // For debugging
    if (observer == NULL)
        return;

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
        throw std::logic_error("add_class type index has to be a class type!");

    if (!(index == class_ptr->get_type()))
        throw std::logic_error("add_class: Index=" + index.describe() + " not the same as class_ptr type=" + class_ptr->get_type().describe());

    // add_class also called for non-C++ type objects such as "namespace"
    //add_ptr_convs(index);

    //classes[index] = class_ptr;

    if (classes2.size() <= index.get_class_id())
        classes2.resize(index.get_class_id()+1, NULL);

    classes2[index.get_class_id()] = class_ptr;

    // This needs to be done at the end so that observers that access the class through type system can get to it.
    for (auto it=observers.begin(); it!=observers.end(); ++it)
        (*it)->register_class(class_ptr);
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
    {
        //return unknown_class;
        throw std::logic_error("No class registered for type " + type.describe());
    }
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
        name = std::string("<unregistered type>");
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


void AbstractTypeSystem::add_ptr_convs(TypeIndex index)
{
    TypeInfoPtr bare = index.get_info()->bare_type();
    add_conv_track<void>(bare);
    add_conv_track<void const>(bare->as_const_obj_type());

    auto bot_tag = BetterTypeInfo::create_index<BottomPtrType>().get_info();

    // allow unsafe_ptr_cast to convert to any type and nil (NULL) to any pointer type
    add_nochange_conv<BottomPtrType, void*>(bot_tag, bare->as_ptr());
    add_nochange_conv<BottomPtrType, void const*>(bot_tag, bare->as_ptr()->as_const_obj_type());

    // allow any ptr to be converted to void* or void const*
    add_nochange_conv<void*, void*>(bare->as_ptr(), BetterTypeInfo::create_index<void*>().get_info());
    add_nochange_conv<void const*, void const*>(bare->as_ptr()->as_const_obj_type(), BetterTypeInfo::create_index<void const*>().get_info());
}

void AbstractTypeSystem::add_converter_variations(TypeIndex from, TypeIndex to, p_conv_t conv)
{
    conv_graph.add_conv(from, to, conv);

    // Add converters to make either type const.
    add_ptr_convs(from);
    add_ptr_convs(to);

    auto from_info = from.get_info();
    auto to_info = to.get_info();

    // Allow converting the object directly to its const form
    conv_graph.add_conv(from, from_info->as_const_obj_type()->get_index(), new NoChangeConv<>);
    conv_graph.add_conv(to, to_info->as_const_obj_type()->get_index(), new NoChangeConv<>);

    // Reuse this converter for just the "to" obj const
    conv_graph.add_conv(from, to.get_info()->as_const_obj_type()->get_index(), conv);

    // Reuse this converter for both from and to as const
    conv_graph.add_conv(from.get_info()->as_const_obj_type()->get_index(), to.get_info()->as_const_obj_type()->get_index(), conv);

    // Allow this expression type to be converted to an expression argument.
    TypeIndex as_expr_type = BetterTypeInfo::create_index<ExprPtr>();
    conv_graph.add_conv(from, as_expr_type, new ToAbstractExpressionConv);
    conv_graph.add_conv(from.get_info()->as_const_obj_type()->get_index(), as_expr_type, new ToAbstractExpressionConv);
    conv_graph.add_conv(to, as_expr_type, new ToAbstractExpressionConv);
    conv_graph.add_conv(to.get_info()->as_const_obj_type()->get_index(), as_expr_type, new ToAbstractExpressionConv);
}


void AbstractTypeSystem::print_conv_chain(TypeIndex from, TypeIndex to) const
{
    conv_graph.print_conv_chain(from, to);
}

void AbstractTypeSystem::add_ptr_conversions(TypeIndex from_type, bool auto_deref)
{
    auto from_nc = from_type.get_info();
    auto from_c =  from_type.get_info()->as_const_obj_type();

    // Allow passing the actual object to things that need the pointer to the object.
    conv_graph.add_conv(from_nc->as_ref()->get_index(), from_nc->as_ptr()->get_index(), new AddrOfConv<AbstractDelegate&, AbstractDelegate*>);
    conv_graph.add_conv( from_c->as_ref()->get_index(),  from_c->as_ptr()->get_index(), new AddrOfConv<AbstractDelegate&, AbstractDelegate*>);

    // Don't want to do this for types convertible to script types, e.g. int*,
    // because then you couldn't return an array; instead the first array element
    // could get converted to a script value if you had this enabled.
    if (auto_deref)
    {
        // Also allow converting pointers back to references.
        conv_graph.add_conv(from_nc->as_ptr()->get_index(), from_nc->as_ref()->get_index(), new PtrDerefConv<AbstractDelegate*, AbstractDelegate&>);
        conv_graph.add_conv( from_c->as_ptr()->get_index(),  from_c->as_ref()->get_index(), new PtrDerefConv<AbstractDelegate*, AbstractDelegate&>);
    }
}
