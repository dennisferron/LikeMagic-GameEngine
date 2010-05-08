#pragma once

#include "../Utility/FuncPtrTraits.hpp"


#include "AbstractCallTargetSelector.hpp"

#include "boost/utility/enable_if.hpp"
#include "boost/type_traits/is_same.hpp"
#include "boost/type_traits/is_void.hpp"

#include "../SFMO/MethodCall.hpp"
#include "../SFMO/CppObjProxy.hpp"

namespace LikeMagic { namespace Marshaling {

using namespace LikeMagic::Utility;
using namespace LikeMagic::SFMO;

template <typename F>
class ProxyMethodSelector : public AbstractCallTargetSelector
{
private:
    F func_ptr;
    AbstractTypeSystem const& type_system;

    typedef FuncPtrTraits<F> Traits;

    typedef typename Traits::TPack TPack;
    typedef typename Traits::IPack IPack;

    typedef typename Traits::R R;

    // This calls a function on the proxy object with return type R
    // and creates a new Term to hold it and returns it in a proxy object.
    template<typename R, typename... Args, int... Indices>
    typename boost::disable_if_c<
        boost::is_void<R>::value || boost::is_same<R, AbstractCppObjProxy*>::value,
            AbstractCppObjProxy*>::type
    do_proxy_op(AbstractCppObjProxy* proxy, ArgList args, TypePack<Args...>, IndexPack<Indices...>) const
    {
        return CppObjProxy<R&>::create(
                Term<R>::create(
                    (proxy->*func_ptr)(type_system.try_conv<Args>(args[Indices])->eval()...)
                ), type_system
        );
    }

    // This calls a function on the proxy which returns a proxy object directly to script.
    template<typename R, typename... Args, int... Indices>
    typename boost::enable_if<
        boost::is_same<R, AbstractCppObjProxy*>,
            AbstractCppObjProxy*>::type
    do_proxy_op(AbstractCppObjProxy* proxy, ArgList args, TypePack<Args...>, IndexPack<Indices...>) const
    {
        return (proxy->*func_ptr)(type_system.try_conv<Args>(args[Indices])->eval()...);
    }

    // This calls a function on the proxy which returns void.
    template<typename R, typename... Args, int... Indices>
    typename boost::enable_if<
        boost::is_void<R>,
            AbstractCppObjProxy*>::type
    do_proxy_op(AbstractCppObjProxy* proxy, ArgList args, TypePack<Args...>, IndexPack<Indices...>) const
    {
        (proxy->*func_ptr)(type_system.try_conv<Args>(args[Indices])->eval()...);
        return 0;
    }

public:

    ProxyMethodSelector(F func_ptr_, AbstractTypeSystem const& type_system_) : func_ptr(func_ptr_), type_system(type_system_) {}

    virtual AbstractCppObjProxy* call(AbstractCppObjProxy* proxy, ArgList args) const
    {
       return do_proxy_op<typename Traits::R>(proxy, args, TPack(), IPack());
    }

    virtual std::vector<BetterTypeInfo> get_arg_types() const
    {
        return Traits::get_arg_types();
    }

};

}}
