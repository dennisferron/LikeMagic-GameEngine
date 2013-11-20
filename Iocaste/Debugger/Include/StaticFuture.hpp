#pragma once

#include "ChainBuilder.hpp"
#include "boost/utility/enable_if.hpp"
#include "boost/type_traits.hpp"
#include "boost/shared_ptr.hpp"
#include <stdexcept>

namespace IoDbg {
/*

After I wrote several input/output components, arranging the code in such a way
that it clearly presents what kind of chain the code is building was obfuscated
by the fact that constructor parameters to the objects necessitated instantiating
the objects in a different order than the order of the chain.

I wanted to be able to write input/output chains with syntax like:

chain.to<A>().to<B>().to<C>()...

But there is a problem: I need to pass C to B's constructor, and pass B to A's constructor,
however with a syntax like the above, A() would be evaluated before B() and B() before C().

My solution is to make the expression "to<X>()" return not the real "X" but a promise to create
"X" in the future, after all the constructor dependencies are available.  This allows me to use a uniform
syntax to create chains of input / output components, without regard to needs of instantiation
order, and then instantiate everything only after the complete chain is described.

*/

template <typename T, typename ConstructorPolicy, typename LeftFuture, typename HeadType, typename... Args>
struct StaticFuture
{
    boost::shared_ptr<T> self;
    LeftFuture lhs;
    std::tuple<Args&&...> args;


    StaticFuture(LeftFuture& lhs_, Args&&... args_)
        : self(), lhs(lhs_), args(std::forward<Args>(args_)...)
    {
    }

    ~StaticFuture()
    {
    }

    HeadType& head()
    {
        return lhs._unwind(*self);
    }

    T& tail()
    {
        return *self;
    }

    StaticFuture complete()
    {
        auto temp = new UnusedType;
        _unwind(*temp);
        delete temp;
        return *this;
    }

    template <typename RHS>
    HeadType& _unwind(RHS& rhs)
    {
        typedef typename MakeIndexPack<sizeof...(Args)>::type IPack;

        if (!self)
            self = boost::shared_ptr<T>(_createSelf(rhs, IPack()));

        return lhs._unwind(*self);
    }

    template <typename RHS, int... Indices>
    T* _createSelf(RHS& rhs, IndexPack<Indices...>)
    {
        typedef decltype(get(ChainPolicy(), *(T*)0)) ConstructorPolicyType;
        return  ChainBuilder<
            T, LeftFuture&, RHS&, ConstructorPolicyType
        >::
            create(lhs, rhs, std::get<Indices>(args)...);
    }

    typedef StaticFuture ThisFuture;

    template <typename Next, typename... NextArgs>
    StaticFuture<Next, ConstructorPolicy, ThisFuture, HeadType, NextArgs...> to(NextArgs&&... args_)
    {
        return StaticFuture<Next, ConstructorPolicy, ThisFuture, HeadType, NextArgs...>(*this, std::forward<NextArgs>(args_)...);
    }

    template <typename T_>
    typename boost::enable_if<
        boost::is_same<T,T_>, int
    >::type count() const
    {
        return 1+lhs.count<T_>();
    }

    template <typename T_>
    typename boost::disable_if<
        boost::is_same<T,T_>, int
    >::type count() const
    {
        return lhs.count<T_>();
    }

    template <typename T_>
    typename boost::enable_if<
        boost::is_same<T,T_>, T_&
    >::type at(int n) const
    {
        int num_preceding = count<T_>();

        if (n==(num_preceding-1))
            return *self;
        else
            return lhs.at<T_>(n);
    }

    template <typename T_>
    typename boost::disable_if<
        boost::is_same<T,T_>, T_&
    >::type at(int n) const
    {
        return lhs.at<T_>(n);
    }
};

template <typename ConstructorPolicy>
struct BeginFuture
{
    template <typename RHS>
    RHS& _unwind(RHS& rhs) { return rhs; }

    template <typename T>
    int count() const { return 0; }

    template <typename T>
    T& at(int n) const
    {
        throw std::out_of_range("Index of StaticFuture at() out of range.");
    }

    template <typename T, typename... NextArgs>
    StaticFuture<T, ConstructorPolicy, BeginFuture, T, NextArgs...> to(NextArgs&&... args_)
    {
        return StaticFuture<T, ConstructorPolicy, BeginFuture, T, NextArgs...>(*this, std::forward<NextArgs>(args_)...);
    }
};

}
