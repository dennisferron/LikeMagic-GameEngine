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

template <typename R, typename F, typename... ArgTypes>
class StaticMethodCall : public Expression<R>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;
    typedef typename MakeIndexPack<sizeof...(ArgTypes)>::type IPack;

private:

    F func;
    ArgTuple args;

    StaticMethodCall(F func_, ArgTuple args_)
        : func(func_), args(args_) {}

public:

    static boost::intrusive_ptr<Expression<R>> create(F func_, ArgTuple args_)
        { return new StaticMethodCall(func_, args_); }

    virtual R eval()
    {
       return call_static_nonvoid(func, args, IPack());
    }

    virtual boost::intrusive_ptr<Expression<R>> clone() const { return new StaticMethodCall(func, methodcall_args::clone_args(args, IPack())); }

    // TODO:  Need new system for determining lazy args.  Static methods do not have access to the target object (maybe pass lazy flag from methodcall generator?)
    virtual bool is_lazy() const { return false; }
    virtual std::string description() const { return methodcall_args::description(args) + " returning " + TypeDescr<R>::text(); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() const
    {
        methodcall_args::mark_args(args, IPack());
    }

};


template <typename F, typename... ArgTypes>
class StaticMethodCall<void, F, ArgTypes...> : public Expression<void>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;
    typedef typename MakeIndexPack<sizeof...(ArgTypes)>::type IPack;

private:

    F func;
    ArgTuple args;

    StaticMethodCall(F func_, ArgTuple args_)
        : func(func_), args(args_) {}

public:

    static boost::intrusive_ptr<Expression<void>> create(F func_, ArgTuple args_)
        { return new StaticMethodCall(func_, args_); }

    virtual void eval()
    {
       call_static_void(func, args, IPack());
    }

    virtual boost::intrusive_ptr<Expression<void>> clone() const
    {
        return new StaticMethodCall(func, methodcall_args::clone_args(args, IPack()));
    }

    // TODO:  Need new system for determining lazy args.  Static methods do not have access to the target object (maybe pass lazy flag from methodcall generator?)
    virtual bool is_lazy() const { return false; }
    virtual std::string description() const { return methodcall_args::description(args); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() const
    {
        methodcall_args::mark_args(args, IPack());
    }

};


}}
