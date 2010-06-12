#pragma once

#include "../Utility/FuncPtrTraits.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "LikeMagic/SFMO/MethodCall.hpp"
#include "LikeMagic/SFMO/CppObjProxy.hpp"

#include "LikeMagic/Marshaling/AbstractCallTargetSelector.hpp"

#include "boost/mpl/if.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

/*
   "We choose to go to the moon in this decade and do the other things,
    not because they are easy, but because they are hard."
    — John F. Kennedy
 */


template <typename T, typename F>
class MethodCallGenerator : public AbstractCallTargetSelector
{
private:
    typedef FuncPtrTraits<F> Traits;

    // Decide whether to generate the call by-ref or by-const-ref.
    // Const functions convert the target to const ref, while
    // nonconst functions convert target to nonconst ref, which
    // fails by design for calling nonconst functions on value types.
    typedef
        typename boost::mpl::if_<boost::is_same<T, StaticMethod>, StaticMethod,
            typename boost::mpl::if_c<Traits::is_const, T const&, T&>::type>::type CallAs;

    F func_ptr;
    AbstractTypeSystem const& type_system;

    typedef typename Traits::TPack TPack;
    typedef typename Traits::IPack IPack;

    typedef typename Traits::R R;

    template<typename... Args, int... Indices>
    boost::intrusive_ptr<Expression<R>>
    build_method_call(ExprPtr target, ArgList args, TypePack<Args...>, IndexPack<Indices...>) const
    {
        if (args.size() != sizeof...(Indices))
            throw std::logic_error("Wrong number of arguments.");

        auto args_tuple = std::make_tuple(type_system.try_conv<Args>(args[Indices])...);

        boost::intrusive_ptr<Expression<R>> method_call = MethodCall<typename Traits::R, CallAs, F, Args...>::create(
            type_system.try_conv<CallAs>(target), func_ptr, args_tuple);

        return method_call;
    }

public:

    //static bool const is_const_func = Traits::is_const;

    MethodCallGenerator(F func_ptr_, AbstractTypeSystem const& type_system_) : func_ptr(func_ptr_), type_system(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
       auto result_proxy = CppObjProxy<typename Traits::R, true>::create(build_method_call(proxy->get_expr(), args, TPack(), IPack()), type_system);
       result_proxy->check_magic();
       return result_proxy;
    }

    virtual std::vector<BetterTypeInfo> get_arg_types() const
    {
        return Traits::get_arg_types();
    }
};

}}
