// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"

#include "LikeMagic/SFMO/CppObjProxy.hpp"
#include "LikeMagic/SFMO/Term.hpp"
#include "LikeMagic/SFMO/Reference.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

// Create as temporary value object.
template <typename ObjT, bool IsCopyable, typename... Args>
class ConstructorCallTarget : public AbstractCallTargetSelector
{
private:

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    AbstractCppObjProxy* construct_obj(AbstractCppObjProxy* proxy, ArgList args, IndexPack<Indices...>) const
    {
        return CppObjProxy<ObjT&, IsCopyable>::create(
                Term<ObjT, IsCopyable>::create(
                    type_system.try_conv<Args>(args[Indices])->eval()...
                ), type_system
        );
    }

public:

    ConstructorCallTarget(AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(proxy, args, IPack());
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const { return false; }
};

// Create by pointer.
template <typename ObjT, bool IsCopyable, typename... Args>
class ConstructorCallTarget<ObjT*, IsCopyable, Args...> : public AbstractCallTargetSelector
{
private:

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    AbstractCppObjProxy* construct_obj(AbstractCppObjProxy* proxy, ArgList args, IndexPack<Indices...>) const
    {
        return CppObjProxy<ObjT*&, IsCopyable>::create(
                Term<ObjT*, IsCopyable>::create(
                    new ObjT(type_system.try_conv<Args>(args[Indices])->eval()...)
                ), type_system
        );
    }

public:

    ConstructorCallTarget(AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(proxy, args, IPack());
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const { return false; }
};

// Create by reference.  This is basically the same as create by value, but wraps the Term in a Reference to disable ToScript conversion.
template <typename ObjT, bool IsCopyable, typename... Args>
class ConstructorCallTarget<ObjT&, IsCopyable, Args...> : public AbstractCallTargetSelector
{
private:

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    AbstractCppObjProxy* construct_obj(AbstractCppObjProxy* proxy, ArgList args, IndexPack<Indices...>) const
    {
        // The Term object will be held onto by an intrusive ptr inside the Reference expression object.
        auto storage_location =
            Term<ObjT, IsCopyable>::create(
                type_system.try_conv<Args>(args[Indices])->eval()...
            )
        ;

        return CppObjProxy<ObjT&, IsCopyable>::create(
            Reference<ObjT>::create(storage_location->eval(), storage_location)
        ,
            type_system
        );
    }

public:

    ConstructorCallTarget(AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(proxy, args, IPack());
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const { return false; }
};

// Create an empty pointer.  This allows you to declare pointer objects suitable for passing to functions that require a ref-to-pointer that they'll store a result in.
template <typename ObjT, bool IsCopyable, typename... Args>
class ConstructorCallTarget<ObjT*&, IsCopyable, Args...> : public AbstractCallTargetSelector
{
private:

    typedef ObjT*& RefPtrObjT;
    typedef Expression<RefPtrObjT> ExprT;
    typedef boost::intrusive_ptr<ExprT> StoreT;

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    AbstractCppObjProxy* construct_obj(AbstractCppObjProxy* proxy, ArgList args, IndexPack<Indices...>) const
    {
        StoreT storage_location =
            Term<ObjT*, IsCopyable>::create(
                NULL
            )
        ;

        return CppObjProxy<ObjT*&, IsCopyable>::create(
            Reference<ObjT*>::create(storage_location->eval(), storage_location)
        ,
            type_system
        );
    }

public:

    ConstructorCallTarget(AbstractTypeSystem const& type_system_) : AbstractCallTargetSelector(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(proxy, args, IPack());
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const { return false; }
};


}}
