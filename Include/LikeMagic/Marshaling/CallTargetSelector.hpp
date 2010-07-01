// LikeMagic C++ Binding Library
// Copyright 2008-2010 Dennis Ferron
// Co-founder DropEcho Studios, LLC.
// Visit our website at dropecho.com.
// 
// LikeMagic is BSD-licensed.
// (See the license file in LikeMagic/Licenses.)


#include "LikeMagic/Marshaling/AbstractCallTargetSelector.hpp"
#include "LikeMagic/Marshaling/MethodCallGenerator.hpp"
#include "LikeMagic/SFMO/AbstractCppObjProxy.hpp"

#include "LikeMagic/Utility/FuncPtrTraits.hpp"

#include <boost/type_traits.hpp>

#pragma once


namespace LikeMagic { namespace Marshaling {

using LikeMagic::AbstractTypeSystem;
using LikeMagic::SFMO::AbstractCppObjProxy;
using namespace LikeMagic::Utility;

// By default, don't create the value target because the type
// might be an abstract class or not copyable.
template <
    template <typename T_, typename F_> class MethodCallImpl,
    typename T, typename F, bool create_value_target=false>
class CallTargetSelector : public AbstractCallTargetSelector
{
public:
    // The struct below selects whether to accept T as a const T or nonconst T.
    //
    // When F is a nonconst function, we'll always return the functionoid
    // for a nonconst T even when the call's target object was actually const.
    // This will result in Functionoid doing a try_conv attempting to convert
    // the object from const to nonconst, which will ordinarily fail, thus
    // preventing nonconst functions from being called on const objects.
    //
    // The specialization(s) of this template on the other hand force the target
    // to always be a "T const" whenever the function is const.  This should have no
    // effect if T was already const, and the conversion to const should always succeed
    // if T was nonconst.  Thus const methods can be called on const and nonconst objects.
    //
    // The way the is_const_func default value works is kinda cool:  even though
    // it appears in the declaration of the non-specialized template, the compiler
    // is smart enough to check it first and select a specialization when the default
    // value evaluates to "true".  That allows us to have the compiler decide between the
    // specialization or the general case without the point-of-use-site for the
    // template even needing to pass the parameter that specializes it!
    template <typename T_, bool is_const_func=MethodCallImpl<T, F>::is_const_func>
    struct FuncTarget { typedef T_ type; };

    template <typename T_>
    struct FuncTarget<T_, true> { typedef T_ const type; };

    typedef typename FuncTarget<T>::type TargetType;

private:
    MethodCallImpl<TargetType&, F> ref_target;
    //MethodCallImpl<TargetType*, F> ptr_target;

public:

    CallTargetSelector(F f, AbstractTypeSystem const& type_sys) :
        ref_target(f, type_sys)
        //ptr_target(f, type_sys)
    {
    }

    virtual AbstractCppObjProxy* call
        (
            AbstractCppObjProxy* target,
            std::vector<boost::intrusive_ptr<AbstractExpression>> args
        ) const
    {
        //if (target->get_type().is_ptr)
        //    return ptr_target.call(target, args);
        /*else*/ if (target->get_type().is_ref)
            return ref_target.call(target, args);
        else
            throw std::logic_error("Methods on this object can only be called by reference or by pointer");
    }

    virtual std::vector<BetterTypeInfo> get_arg_types() const
    {
        return ref_target.get_arg_types();
    }
};

/*

// On the other hand if we are creating the value target, extend the previous with the addition of value-target calls.
template <
    template <typename T_, typename F_> class MethodCallImpl,
    typename T, typename F>
class CallTargetSelector<MethodCallImpl, T, F, true> : public CallTargetSelector<MethodCallImpl, T, F>
{
private:
    MethodCallImpl<typename CallTargetSelector<MethodCallImpl, T, F>::TargetType, F> value_target;

public:

    CallTargetSelector(F f, AbstractTypeSystem const& type_sys) :
        CallTargetSelector<MethodCallImpl, T, F>::CallTargetSelector(f, type_sys),
        value_target(f, type_sys)
    {
    }

    virtual AbstractCppObjProxy* call
        (
            AbstractCppObjProxy* target,
            std::vector<boost::intrusive_ptr<AbstractExpression>> args
        ) const
    {
        if (target->get_type().is_ptr || target->get_type().is_ref)
            return CallTargetSelector<MethodCallImpl, T, F>::call(target, args);
        else
            return value_target.call(target, args);
    }
};

*/

}}
