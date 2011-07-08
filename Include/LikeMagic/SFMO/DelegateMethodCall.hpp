// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#pragma once

#include "Expression.hpp"

#include "LikeMagic/Utility/TypeDescr.hpp"
//#include "LikeMagic/Utility/FuncPtrTraits.hpp"
//#include "LikeMagic/Utility/MakeCall.hpp"

#include "LikeMagic/SFMO/methodcall_args.hpp"

namespace LikeMagic { namespace SFMO {

using namespace LikeMagic::Utility;

// Nonconst, nonvoid
template <typename R, bool is_const, typename IPack, typename... ArgTypes>
class DelegateMethodCall : public Expression<R>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;

private:
    typedef R (AbstractDelegate::*F)(ArgTypes...);
    typedef AbstractDelegate& ObjType;

    boost::intrusive_ptr<Expression<ObjType>> target;
    F func;
    ArgTuple args;

    DelegateMethodCall(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        : target(target_), func(func_), args(args_) {}

    template <int... Indices>
    inline R eval_with_indices(IndexPack<Indices...>)
    {
        return ((target->eval()).*func)(std::get<Indices>(args)->eval()...);
    }

public:

    inline static boost::intrusive_ptr<Expression<R>> create(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        { return new DelegateMethodCall(target_, func_, args_); }

    virtual R eval()
    {
        return eval_with_indices(IPack());
    }

    virtual boost::intrusive_ptr<Expression<R>> clone() const
    {
        throw std::logic_error("Clone LikeMagic delegate method call not implemented.");
    }

    // DelegateMethodCall is lazy if target is lazy; we deliberately do NOT check for lazy args;
    // passing a lazy expression as an argument to an eager method call forces evaluation of the lazy arg!
    virtual bool is_lazy() const { return target->is_lazy(); }
    virtual std::string description() const { return methodcall_args::description(target, args) + " returning " + TypeDescr<R>::text(); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(target, args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() const
    {
        target->mark();
        methodcall_args::mark_args(args, IPack());
    }

};

// void, nonconst
template <typename IPack, typename... ArgTypes>
class DelegateMethodCall<void, false, IPack, ArgTypes...> : public Expression<void>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;

private:
    typedef void (AbstractDelegate::*F)(ArgTypes...);
    typedef AbstractDelegate& ObjType;

    boost::intrusive_ptr<Expression<ObjType>> target;
    F func;
    ArgTuple args;

    DelegateMethodCall(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        : target(target_), func(func_), args(args_) {}

    template <int... Indices>
    inline void eval_with_indices(IndexPack<Indices...>)
    {
        ((target->eval()).*func)(std::get<Indices>(args)->eval()...);
    }

public:

    inline static boost::intrusive_ptr<Expression<void>> create(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        { return new DelegateMethodCall(target_, func_, args_); }

    virtual void eval()
    {
        eval_with_indices(IPack());
    }

    virtual boost::intrusive_ptr<Expression<void>> clone() const
    {
        throw std::logic_error("Clone LikeMagic delegate method call not implemented.");
    }

    // MethodCall is lazy if target is lazy; we deliberately do NOT check for lazy args;
    // passing a lazy expression as an argument to an eager method call forces evaluation of the lazy arg!
    virtual bool is_lazy() const { return target->is_lazy(); }
    virtual std::string description() const { return methodcall_args::description(target, args); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(target, args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() const
    {
        target->mark();
        methodcall_args::mark_args(args, IPack());
    }

};

// nonvoid, const
template <typename R, typename IPack, typename... ArgTypes>
class DelegateMethodCall<R, true, IPack, ArgTypes...> : public Expression<R>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;

private:
    typedef R (AbstractDelegate::*F)(ArgTypes...) const;
    typedef AbstractDelegate const& ObjType;

    boost::intrusive_ptr<Expression<ObjType>> target;
    F func;
    ArgTuple args;

    DelegateMethodCall(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        : target(target_), func(func_), args(args_) {}

    template <int... Indices>
    inline R eval_with_indices(IndexPack<Indices...>)
    {
        return ((target->eval()).*func)(std::get<Indices>(args)->eval()...);
    }

public:

    inline static boost::intrusive_ptr<Expression<R>> create(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        { return new DelegateMethodCall(target_, func_, args_); }

    virtual R eval()
    {
        return eval_with_indices(IPack());
    }

    virtual boost::intrusive_ptr<Expression<R>> clone() const
    {
        throw std::logic_error("Clone LikeMagic delegate method call not implemented.");
    }

    // DelegateMethodCall is lazy if target is lazy; we deliberately do NOT check for lazy args;
    // passing a lazy expression as an argument to an eager method call forces evaluation of the lazy arg!
    virtual bool is_lazy() const { return target->is_lazy(); }
    virtual std::string description() const { return methodcall_args::description(target, args) + " returning " + TypeDescr<R>::text(); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(target, args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() const
    {
        target->mark();
        methodcall_args::mark_args(args, IPack());
    }

};

// void, const
template <typename IPack, typename... ArgTypes>
class DelegateMethodCall<void, true, IPack, ArgTypes...> : public Expression<void>
{
public:
    typedef std::tuple<boost::intrusive_ptr<Expression<ArgTypes>>...> ArgTuple;

private:
    typedef void (AbstractDelegate::*F)(ArgTypes...) const;
    typedef AbstractDelegate const& ObjType;

    boost::intrusive_ptr<Expression<ObjType>> target;
    F func;
    ArgTuple args;

    DelegateMethodCall(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        : target(target_), func(func_), args(args_) {}

    template <int... Indices>
    inline void eval_with_indices(IndexPack<Indices...>)
    {
        ((target->eval()).*func)(std::get<Indices>(args)->eval()...);
    }

public:

    inline static boost::intrusive_ptr<Expression<void>> create(boost::intrusive_ptr<Expression<ObjType>> target_, F func_, ArgTuple args_)
        { return new DelegateMethodCall(target_, func_, args_); }

    virtual void eval()
    {
        eval_with_indices(IPack());
    }

    virtual boost::intrusive_ptr<Expression<void>> clone() const
    {
        throw std::logic_error("Clone LikeMagic delegate method call not implemented.");
    }

    // MethodCall is lazy if target is lazy; we deliberately do NOT check for lazy args;
    // passing a lazy expression as an argument to an eager method call forces evaluation of the lazy arg!
    virtual bool is_lazy() const { return target->is_lazy(); }
    virtual std::string description() const { return methodcall_args::description(target, args); }
    virtual bool is_terminal() const { return false; }
    virtual std::set<AbstractObjectSet*> get_objsets() const { return methodcall_args::get_objsets(target, args); }

    // mark Io objects held by this object so the garbage collector won't free them
    virtual void mark() const
    {
        target->mark();
        methodcall_args::mark_args(args, IPack());
    }

};



}}
