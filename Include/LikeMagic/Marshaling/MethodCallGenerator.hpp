#pragma once

#include "../Utility/FuncPtrTraits.hpp"


#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "../SFMO/MethodCall.hpp"
#include "../SFMO/CppObjProxy.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

/*
   "We choose to go to the moon in this decade and do the other things,
    not because they are easy, but because they are hard."
    — John F. Kennedy
 */


template <typename CallAs, typename F>
class MethodCallGenerator : public AbstractCallTargetSelector
{
private:
    F func_ptr;
    AbstractTypeSystem const& type_system;

    typedef FuncPtrTraits<F> Traits;

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

    static bool const is_const_func = Traits::is_const;

    MethodCallGenerator(F func_ptr_, AbstractTypeSystem const& type_system_) : func_ptr(func_ptr_), type_system(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
       auto result_proxy = CppObjProxy<typename Traits::R>::create(build_method_call(proxy->get_expr(), args, TPack(), IPack()), type_system);
       result_proxy->check_magic();
       return result_proxy;
    }

    virtual std::vector<BetterTypeInfo> get_arg_types() const
    {
        return Traits::get_arg_types();
    }
};

}}
