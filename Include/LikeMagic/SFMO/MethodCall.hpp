// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "Expression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
#include "LikeMagic/Utility/FuncPtrTraits.hpp"
#include "LikeMagic/Utility/MakeCall.hpp"

#include "LikeMagic/SFMO/methodcall_args.hpp"

namespace LikeMagic { namespace SFMO {

using namespace LikeMagic::Utility;

template <typename R, typename ObjType, typename F, typename... ArgTypes>
class MethodCall : public Expression<R>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;
    typedef typename MakeIndexPack<sizeof...(ArgTypes)>::type IPack;

private:

    boost::intrusive_ptr<Expression<ObjType>> target;
    F func;
    ArgTuple args;

    MethodCall(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        : target(target_), func(func_), args(args_) {}

public:

    static boost::intrusive_ptr<Expression<R>> create(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        { return new MethodCall(target_, func_, args_); }

    virtual R eval()
    {
       return MakeCall<ObjType>::call_nonvoid(target->eval(), func, args, IPack());
    }

    virtual boost::intrusive_ptr<Expression<R>> clone() const { return new MethodCall(target, func, methodcall_args::clone_args(args, IPack())); }

    // MethodCall is lazy if target is lazy; we deliberately do NOT check for lazy args;
    // passing a lazy expression as an argument to an eager method call forces evaluation of the lazy arg!
    virtual bool is_lazy() const { return target->is_lazy(); }
    virtual std::string description() const { return methodcall_args::description(target, args) + " returning " + TypeDescr<R>::text(); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(target, args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark()
    {
        target->mark();
        methodcall_args::mark_args(args, IPack());
    }

};


template <typename ObjType, typename F, typename... ArgTypes>
class MethodCall<void, ObjType, F, ArgTypes...> : public Expression<void>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;
    typedef typename MakeIndexPack<sizeof...(ArgTypes)>::type IPack;

private:

    boost::intrusive_ptr<Expression<ObjType>> target;
    F func;
    ArgTuple args;

    MethodCall(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        : target(target_), func(func_), args(args_) {}

public:

    static boost::intrusive_ptr<Expression<void>> create(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        { return new MethodCall(target_, func_, args_); }

    virtual void eval()
    {
       MakeCall<ObjType>::call_void(target->eval(), func, args, IPack());
    }

    virtual boost::intrusive_ptr<Expression<void>> clone() const
    {
        // TODO:  decide whether target should be cloned!
        return new MethodCall(target, func, methodcall_args::clone_args(args, IPack()));
    }

    // MethodCall is lazy if target is lazy; we deliberately do NOT check for lazy args;
    // passing a lazy expression as an argument to an eager method call forces evaluation of the lazy arg!
    virtual bool is_lazy() const { return target->is_lazy(); }
    virtual std::string description() const { return methodcall_args::description(target, args); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(target, args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark()
    {
        target->mark();
        methodcall_args::mark_args(args, IPack());
    }

};


}}
