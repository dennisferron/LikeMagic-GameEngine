// LikeMagic C++ Binding Library
// Copyright 2008-2011 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
//
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)

#pragma once

#include "LikeMagic/CallTargets/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Generators/MemberKind.hpp"

namespace LikeMagic { namespace Generators {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;
using namespace LikeMagic::CallTargets;

template <MemberKind FMod, typename R, typename... Args>
class DeferredCallGenerator : public AbstractCallTargetSelector
{
public:
    typedef R (AbstractDelegate::*F)(Args...);

private:

    F func_ptr;
    TypeIndex actual_type;

public:

    DeferredCallGenerator(TypeIndex ref_type, TypeIndex const_ref_type, F func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_), actual_type(ref_type)
    {
    }

    // TODO:  add a way for this to report its function pointer and be replaced.

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        throw std::logic_error("Missing delegate call generator at WantsCallGenerator site.");
    }

    virtual TypeInfoList get_arg_types() const
    {
        // TODO:  Needed?
        //return make_arg_list(TypePack<Args...>());
        throw std::logic_error("Missing delegate call generator at WantsCallGenerator site.");
    }
};

template <typename R, typename... Args>
class DeferredCallGenerator<MemberKind::member_const, R, Args...> : public AbstractCallTargetSelector
{
public:
    typedef R (AbstractDelegate::*F)(Args...) const;

private:

    F func_ptr;
    TypeIndex actual_type;

public:

    DeferredCallGenerator(TypeIndex ref_type, TypeIndex const_ref_type, F func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_), actual_type(const_ref_type)
    {
    }

    // TODO:  add a way for this to report its function pointer and be replaced.
    // don't forget that the const matters

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        throw std::logic_error("Missing delegate call generator at DeferredCallGenerator site.");
    }

    virtual TypeInfoList get_arg_types() const
    {
        // TODO:  Needed?
        //return make_arg_list(TypePack<Args...>());
        throw std::logic_error("Missing delegate call generator at DeferredCallGenerator site.");
    }
};


// Static methods that pass the object as first argument (e.g., nonmember operators).
template <typename R, typename... Args>
class DeferredCallGenerator<MemberKind::nonmember_op, R, Args...> : public AbstractCallTargetSelector
{
public:
    typedef R (*F)(Args...);

private:

    F func_ptr;
    TypeIndex actual_type;

public:

    DeferredCallGenerator(TypeIndex ref_type, TypeIndex const_ref_type, F func_ptr_, AbstractTypeSystem const& type_system_)
        : AbstractCallTargetSelector(type_system_), func_ptr(func_ptr_), actual_type(BetterTypeInfo::create_index<StaticMethod>())
    {
    }

    // TODO:  add a way for this to report its function pointer and be replaced.
    // Don't forget that the type list matters

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
        throw std::logic_error("Missing delegate call generator at DeferredCallGenerator site.");
    }

    virtual TypeInfoList get_arg_types() const
    {
        throw std::logic_error("Missing delegate call generator at DeferredCallGenerator site.");
        /*
        // TODO:  Needed?
        TypeInfoList args = make_arg_list(TypePack<Args...>());

        // Have to report that we take 1 less arg, because "this" object is the first arg.
        args.erase(args.begin());

        return args;
        */
    }
};


}}
