// LikeMagic C++ Binding Library
// Copyright 2008-2013 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/TypeSystem.hpp"
#include "LikeMagic/CallTargets/CallTarget.hpp"

#include "LikeMagic/Exprs/Term.hpp"
#include "LikeMagic/Exprs/Reference.hpp"

namespace LikeMagic { namespace CallTargets {

using namespace LikeMagic::Utility;
using namespace LikeMagic::Exprs;

// Create as temporary value object.
template <typename ObjT, bool IsCopyable, typename... Args>
class ConstructorCallTarget : public CallTarget
{
private:

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    ExprPtr construct_obj(ArgList args, IndexPack<Indices...>) const
    {
        return Term<ObjT, IsCopyable>::create(
                    type_system->try_conv<Args>(args[Indices])->eval()...
                );
    }

public:

    ConstructorCallTarget() {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(args, IPack());
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
class ConstructorCallTarget<ObjT*, IsCopyable, Args...> : public CallTarget
{
private:

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    ExprPtr construct_obj(ArgList args, IndexPack<Indices...>) const
    {
        return Term<ObjT*, IsCopyable>::create(
                    new ObjT(type_system->try_conv<Args>(args[Indices])->eval()...)
                );
    }

public:

    ConstructorCallTarget() {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(args, IPack());
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
class ConstructorCallTarget<ObjT&, IsCopyable, Args...> : public CallTarget
{
private:

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    ExprPtr construct_obj(ArgList args, IndexPack<Indices...>) const
    {
        // The Term object will be held onto by an intrusive ptr inside the Reference expression object.
        auto storage_location =
            Term<ObjT, IsCopyable>::create(
                type_system->try_conv<Args>(args[Indices])->eval()...
            )
        ;

        return Reference<ObjT>::create(storage_location->eval(), storage_location);
    }

public:

    ConstructorCallTarget() {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(args, IPack());
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
class ConstructorCallTarget<ObjT*&, IsCopyable, Args...> : public CallTarget
{
private:

    typedef ObjT*& RefPtrObjT;
    typedef Expression<RefPtrObjT> ExprT;
    typedef boost::intrusive_ptr<ExprT> StoreT;

    // This calls the Term::create function that constructs the object based on args.
    template<int... Indices>
    ExprPtr construct_obj(ArgList args, IndexPack<Indices...>) const
    {
        StoreT storage_location =
            Term<ObjT*, IsCopyable>::create(
                NULL
            )
        ;

        return Reference<ObjT*>::create(storage_location->eval(), storage_location);
    }

public:

    ConstructorCallTarget() {}

    virtual ExprPtr call(ExprPtr target, ArgList args) const
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;
        return construct_obj(args, IPack());
    }

    virtual TypeInfoList get_arg_types() const
    {
        return make_arg_list(TypePack<Args...>());
    }

    // Some methods (like constructors) should not be inherited.
    virtual bool is_inherited() const { return false; }
};


}}
